#include "MonitorSystem.h"

#include <windows.h>
#include "../Globals.h"
#include "../GlobalFuncs.h"
#include "../Defines.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <luabind/class.hpp>
#include <luabind/detail/call_function.hpp>
#include "../LuaMain/LuaHelper.h"

// 10 monitors is the max Windows supports
MonitorSystemMonitors monitorInformation[9];
int numberOfMonitors = -1;

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    numberOfMonitors = numberOfMonitors + 1;
    MONITORINFOEX info;
    info.cbSize = sizeof(info);

    if (GetMonitorInfo(hMonitor, &info))
    {
        monitorInformation[numberOfMonitors].index = numberOfMonitors + 1;
        monitorInformation[numberOfMonitors].monitorLeft = info.rcMonitor.left;
        monitorInformation[numberOfMonitors].monitorRight = info.rcMonitor.right;
        monitorInformation[numberOfMonitors].monitorTop = info.rcMonitor.top;
        monitorInformation[numberOfMonitors].monitorBottom = info.rcMonitor.bottom;

        monitorInformation[numberOfMonitors].monitorX = (info.rcMonitor.left - info.rcMonitor.right);
        monitorInformation[numberOfMonitors].monitorY = (info.rcMonitor.top - info.rcMonitor.bottom);
        monitorInformation[numberOfMonitors].monitorWidth = (info.rcMonitor.right - info.rcMonitor.left);
        monitorInformation[numberOfMonitors].monitorHeight = (info.rcMonitor.bottom - info.rcMonitor.top);

        monitorInformation[numberOfMonitors].monitorName = (WCHAR)info.szDevice;
    }

    return TRUE;
}

void MonitorSystem::SetupMonitors()
{
    For(i, 0, 9)
    {
        monitorInformation[i].Reset();
    }

    bool monitorSuccess = EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

    int monitorCountToCompare = GetSystemMetrics(SM_CMONITORS);
    numberOfMonitors = numberOfMonitors + 1; // To make sure that Lua is compatible with this
    if(numberOfMonitors != monitorCountToCompare)
    {
        MessageBoxA(NULL, "Looks like the size comparison is false", "Test", NULL);
    }
}

int MonitorSystem::GetScreenXPosition()
{
    RECT rect;
    GetWindowRect(gMainWindowHwnd, &rect);
    int x = rect.left;
    return x;
}

int MonitorSystem::GetScreenYPosition()
{
    RECT rect;
    GetWindowRect(gMainWindowHwnd, &rect);
    int y = rect.top;
    return y;
}

int MonitorSystem::GetScreenCenterXPosition(int monitorID)
{
    int posx = monitorInformation[monitorID].monitorWidth / 2 - (monitorInformation[monitorID].monitorRight - monitorInformation[monitorID].monitorLeft) / 2;
    return posx;
}

int MonitorSystem::GetScreenCenterYPosition(int monitorID)
{
    int posy = monitorInformation[monitorID].monitorHeight / 2 - (monitorInformation[monitorID].monitorBottom - monitorInformation[monitorID].monitorTop) / 2;
    return posy;
}

int MonitorSystem::GetScreenResolutionWidth(int monitorID)
{
    return monitorInformation[monitorID].monitorWidth;
}

int MonitorSystem::GetScreenResolutionHeight(int monitorID)
{
    return monitorInformation[monitorID].monitorHeight;
}

int MonitorSystem::GetScreenX(int monitorID)
{
    return monitorInformation[monitorID].monitorX;
}

int MonitorSystem::GetScreenY(int monitorID)
{
    return monitorInformation[monitorID].monitorY;
}

// This will center the window to the screen. Useful for auto-moving the window to the center if you want to reset where X2 was when starting up the engine. monitorID will center to that specific monitor.
void MonitorSystem::CenterWindow(int monitorID)
{
    int x, y;
    x = monitorInformation[monitorID].monitorWidth / 2 - (monitorInformation[monitorID].monitorRight - monitorInformation[monitorID].monitorLeft) / 2,
    y = monitorInformation[monitorID].monitorHeight / 2 - (monitorInformation[monitorID].monitorBottom - monitorInformation[monitorID].monitorTop) / 2,

    // When getting everything set, center the window!
    SetWindowPos(gMainWindowHwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void MonitorSystem::SetWindowPosition(int x, int y)
{
    SetWindowPos(gMainWindowHwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

static luabind::object getMonitorInfo(int monitorID, lua_State *L)
{
    int realIndex = monitorID - 1;
    if(monitorID < 1 && monitorID > numberOfMonitors || std::to_string(monitorInformation[realIndex].index).length() == 0)
    {
        luabind::object outData = luabind::newtable(L);
        outData["invalid"] = "monitor";
        return outData;
    }
    else
    {
        wchar_t monitorNameDraft = monitorInformation[realIndex].monitorName;
        std::wstring monitorName(1, monitorNameDraft);
        luabind::object outData = luabind::newtable(L);

        outData["index"] = monitorInformation[realIndex].index;
        outData["monitorLeft"] = monitorInformation[realIndex].monitorLeft;
        outData["monitorRight"] = monitorInformation[realIndex].monitorRight;
        outData["monitorTop"] = monitorInformation[realIndex].monitorTop;
        outData["monitorBottom"] = monitorInformation[realIndex].monitorBottom;
        outData["monitorX"] = monitorInformation[realIndex].monitorX;
        outData["monitorY"] = monitorInformation[realIndex].monitorY;
        outData["monitorWidth"] = monitorInformation[realIndex].monitorWidth;
        outData["monitorHeight"] = monitorInformation[realIndex].monitorHeight;
        outData["monitorName"] = WStr2Str(monitorName);

        return outData;
    }
}

luabind::object MonitorSystem::GetMonitorInfo(int monitorID, lua_State *L)
{
    return getMonitorInfo(monitorID, L);
}
