#include "MouseHandler.h"
#include "../Rendering/WindowSizeHandler.h"
#include "../Globals.h"
#include <windows.h>
#include <winreg.h>

// Global instance
MouseHandler gMouseHandler;

static DWORD GetDWORDRegKey(HKEY hKey, const std::wstring &strValueName, DWORD &nValue)
{
    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    DWORD nError = ::RegQueryValueExW(hKey,
        strValueName.c_str(),
        0,
        NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        nValue = nResult;
    }
    return nError;
}

// A way to get the mouse settings from the Registry.
void MouseHandler::getMouseInfo()
{
    if(!mMouseInfoGotten)
    {
        std::wstring regSubKeyCursor1 = L"SOFTWARE\\Microsoft\\";
        std::wstring regGroupCursor1 = L"Accessibility\\";
        std::wstring regSubKeyCursor2 = L"Control Panel\\";
        std::wstring regGroupCursor2 = L"Cursors";
        std::wstring cursorSizeReg = L"CursorSize";
        std::wstring cursorColorReg = L"CursorColor";
        std::wstring cursorTypeReg = L"CursorType";
        std::wstring cursorBaseSizeReg = L"CursorBaseSize";
        DWORD cursorSize = 0;
        DWORD cursorColor = 0;
        DWORD cursorType = 0;
        DWORD cursorBaseSize = 0;

        GetDWORDRegKey(HKEY_CURRENT_USER, regSubKeyCursor1 + regGroupCursor1 + cursorSizeReg, cursorSize);
        GetDWORDRegKey(HKEY_CURRENT_USER, regSubKeyCursor1 + regGroupCursor1 + cursorColorReg, cursorColor);
        GetDWORDRegKey(HKEY_CURRENT_USER, regSubKeyCursor1 + regGroupCursor1 + cursorTypeReg, cursorType);
        GetDWORDRegKey(HKEY_CURRENT_USER, regSubKeyCursor2 + regGroupCursor2 + cursorBaseSizeReg, cursorBaseSize);

        mClientSize = (int)cursorSize;
        mClientColor = (int)cursorColor;
        mClientType = (int)cursorType;
        mClientBaseSize = (int)cursorBaseSize;

        mMouseInfoGotten = true;
    }
    else
    {
        return;
    }
}

void MouseHandler::OnMouseMove(int x, int y, uint8_t buttonState)
{
    if (mInClientArea && (mClientX == x) && (mClientY == y))
    {
        // No change.
        return;
    }

    if ((!mInClientArea) && (gMainWindowHwnd != nullptr))
    {
        // Make sure we get WM_MOUSELEAVE
        TRACKMOUSEEVENT params;
        params.cbSize = sizeof(params);
        params.dwFlags = TME_LEAVE;
        params.hwndTrack = gMainWindowHwnd;
        params.dwHoverTime = 0;
        TrackMouseEvent(&params);
    }

    mClientX = x;
    mClientY = y;
    mButtonState = buttonState;
    mInClientArea = true;
    Recalculate();
}

void MouseHandler::OnMouseLeave()
{
    if (mInClientArea)
    {
        mInClientArea = false;
        Recalculate();
    }
}

void MouseHandler::OnMouseButtonEvent(ButtonEnum button, ButtonEvtEnum state)
{
    if (gLunaLua.isValid() && !LunaMsgBox::IsActive()) {
        std::shared_ptr<Event> event = std::make_shared<Event>("onMouseButtonEvent", false);
        event->setDirectEventName("onMouseButtonEvent");
        event->setLoopable(false);
        gLunaLua.callEvent(event, button, state, mFramebufferX, mFramebufferY);
    }
}

void MouseHandler::OnMouseWheelEvent(WheelEnum wheel, int delta)
{
    if (gLunaLua.isValid() && !LunaMsgBox::IsActive()) {
        std::shared_ptr<Event> event = std::make_shared<Event>("onMouseWheelEvent", false);
        event->setDirectEventName("onMouseWheelEvent");
        event->setLoopable(false);
        gLunaLua.callEvent(event, wheel, delta, mFramebufferX, mFramebufferY);
    }
}

// Recalculate FB coordinates
void MouseHandler::Recalculate()
{
    if (mInClientArea)
    {
        double newX = mClientX;
        double newY = mClientY;
        gWindowSizeHandler.WindowToFramebuffer(newX, newY);
        mFramebufferX = newX;
        mFramebufferY = newY;
    }
    else
    {
        mFramebufferX = NAN;
        mFramebufferY = NAN;
    }
}

int MouseHandler::getSizeRaw()
{
    return mClientSize;
}

int MouseHandler::getBaseSizeRaw()
{
    return mClientBaseSize;
}

/*  1 = 12 x 19
    2 = 20 x 29
    3 = 27 x 38
    4 = 33 x 47
    5 = 39 x 57
    6 = 45 x 66
    7 = 53 x 77
    8 = 60 x 87
    
    I didn't count the rest, but you know, it gets bigger
*/

int MouseHandler::getWidth()
{
    int mouseSizeBase = gMouseHandler.getBaseSizeRaw();
    int mouseSize = gMouseHandler.getSizeRaw();
    // Mouse size differences
    int widthDifference = 0.14;
    int widthIncrease = 0.56;
    
    mClientWidth = mouseSize * (widthIncrease + widthDifference) * 9;

    return mClientWidth;
}

int MouseHandler::getHeight()
{
    int mouseSizeBase = gMouseHandler.getBaseSizeRaw();
    int mouseSize = gMouseHandler.getSizeRaw();
    // Mouse size differences
    int heightDifference = 0.01;
    int heightIncrease = 0.64;
    
    mClientHeight = mouseSize * (heightIncrease + heightDifference) * 12;
    
    return mClientHeight;
}
