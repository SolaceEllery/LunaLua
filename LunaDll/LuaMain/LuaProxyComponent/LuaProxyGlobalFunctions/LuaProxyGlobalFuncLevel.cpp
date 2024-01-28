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

bool LuaProxy::Level::load(std::string levelName, std::string episodeName, int warpIdx, bool useLoadSFX)
{
    gIsLoadingLevelLuaName = levelName;
    gIsLoadingLevelLuaWarpID = warpIdx;
    gIsLoadingLevelLuaEpisodeName = episodeName;
    gIsLoadingLevelLuaSuppressSFX = useLoadSFX;
    gIsLoadingLevelLua = true;
    return true;
}

bool LuaProxy::Level::load(std::string levelName)
{
    gIsLoadingLevelLuaName = levelName;
    gIsLoadingLevelLuaWarpID = 0;
    gIsLoadingLevelLuaEpisodeName = "";
    gIsLoadingLevelLuaSuppressSFX = true;
    gIsLoadingLevelLua = true;
    return true;
}

bool LuaProxy::Level::load(std::string levelName, std::string episodeName)
{
    gIsLoadingLevelLuaName = levelName;
    gIsLoadingLevelLuaWarpID = 0;
    gIsLoadingLevelLuaEpisodeName = episodeName;
    gIsLoadingLevelLuaSuppressSFX = true;
    gIsLoadingLevelLua = true;
    return true;
}

bool LuaProxy::Level::load(std::string levelName, std::string episodeName, int warpIdx)
{
    gIsLoadingLevelLuaName = levelName;
    gIsLoadingLevelLuaWarpID = warpIdx;
    gIsLoadingLevelLuaEpisodeName = episodeName;
    gIsLoadingLevelLuaSuppressSFX = true;
    gIsLoadingLevelLua = true;
    return true;
}
