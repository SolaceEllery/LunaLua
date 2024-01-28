#include "../../LuaProxy.h"
#include "../../../Defines.h"
#include "../../../GlobalFuncs.h"
#include "../../LunaLuaMain.h"
#include "../../../Globals.h"

std::string LuaProxy::Level::filename()
{
    return (std::string)GM_LVLFILENAME_PTR;
}

std::string LuaProxy::Level::name()
{
    return (std::string)GM_LVLNAME_PTR;
}
