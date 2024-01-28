#include "../../LuaProxy.h"
#include "../../../Defines.h"
#include "../../../GlobalFuncs.h"

std::string LuaProxy::Level::filename()
{
    return (std::string)GM_LVLFILENAME_PTR;
}

std::string LuaProxy::Level::name()
{
    return (std::string)GM_LVLNAME_PTR;
}

bool LuaProxy::Level::load(std::string levelName, std::string episodeName, int warpIdx, bool useLoadSFX)
{
    return LoadLevel(levelName, warpIdx, episodeName, 1, useLoadSFX);
}

bool LuaProxy::Level::load(std::string levelName)
{
    return LuaProxy::Level::load(levelName, "", 0, false);
}

bool LuaProxy::Level::load(std::string levelName, std::string episodeName)
{
    return LuaProxy::Level::load(levelName, episodeName, 0, false);
}

bool LuaProxy::Level::load(std::string levelName, std::string episodeName, int warpIdx)
{
    return LuaProxy::Level::load(levelName, episodeName, warpIdx, false);
}
