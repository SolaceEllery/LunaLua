#ifndef MonitorSystem_hhh
#define MonitorSystem_hhh

#include <windows.h>

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <luabind/class.hpp>
#include <luabind/detail/call_function.hpp>
#include "../LuaMain/LuaHelper.h"

struct MonitorSystemMonitors
{
    int index;
    int monitorLeft;
    int monitorRight;
    int monitorTop;
    int monitorBottom;
    int monitorX;
    int monitorY;
    int monitorWidth;
    int monitorHeight;
    WCHAR monitorName;
    
    MonitorSystemMonitors()
    {
        Reset();
    }
    
    void Reset()
    {
        index = 0;
        monitorLeft = 0;
        monitorRight = 0;
        monitorTop = 0;
        monitorBottom = 0;
        monitorX = 0;
        monitorY = 0;
        monitorWidth = 0;
        monitorHeight = 0;
        monitorName = (WCHAR)"";
    }
};

extern int numberOfMonitors;
extern MonitorSystemMonitors monitorInformation[9];

namespace MonitorSystem{
    void SetupMonitors();

    int GetScreenXPosition();
    int GetScreenYPosition();
    int GetScreenCenterXPosition(int monitorID);
    int GetScreenCenterYPosition(int monitorID);
    
    int GetScreenResolutionWidth(int monitorID);
    int GetScreenResolutionHeight(int monitorID);
    int GetScreenX(int monitorID);
    int GetScreenY(int monitorID);
    
    void CenterWindow(int monitorID);
    void SetWindowPosition(int x, int y);
    
    luabind::object GetMonitorInfo(int monitorID, lua_State *L);
};

#endif
