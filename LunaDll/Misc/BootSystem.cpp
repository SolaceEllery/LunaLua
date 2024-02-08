#include <thread>
#include <atomic>
#include <string>
#include "../Globals.h"
#include "../Defines.h"
#include "../GlobalFuncs.h"
#include "AsmPatch.h"
#include "../Rendering/GL/GLEngine.h"
#include "../Rendering/GL/GLContextManager.h"
#include "../Rendering/Rendering.h"
#include "../Rendering/WindowSizeHandler.h"
#include <lua.hpp>
#include "LoadScreen.h"
#include "../LuaMain/LunaPathValidator.h"
#include "../SdlMusic/MusicManager.h"

static void luasetconst(lua_State* L, const char* name, lua_Number number)
{
    lua_pushnumber(L, number);
    lua_setglobal(L, name);
}

#define DEF_CONST(L, C) luasetconst(L, #C, C)

extern void InitMinimalLuaState(lua_State* L);

static lua_State* bootScreenGetLuaState()
{
    // These NEED to be set, otherwise loadfile will error
    GM_FULLDIR = gEpisodeSettings.episodeDirectory + L"\\";
    gLunaPathValidator.SetPaths();

    static std::string mainCode;
    if (mainCode.length() == 0)
    {
        std::wstring lapi = gAppPathWCHAR;
        lapi = lapi.append(L"\\scripts\\base\\engine\\bootscreen.lua");

        FILE* theFile = _wfopen(lapi.c_str(), L"rb");
        if (!theFile)
        {
            return nullptr;
        }
        fseek(theFile, 0, SEEK_END);
        size_t len = ftell(theFile);
        rewind(theFile);
        if (len > 0)
        {
            mainCode.resize(len);
            fread(&mainCode[0], 1, len, theFile);
        }
        fclose(theFile);
    }

    static lua_State* L = nullptr;
    if (L == nullptr)
    {
        L = luaL_newstate();

        InitMinimalLuaState(L);
        
        lua_pushboolean(L, gEpisodeSettings.usingCustomSplash);
        lua_setglobal(L, "_useCustomSplash");

        lua_pushstring(L, WStr2Str(gEpisodeSettings.episodeBootImage).c_str());
        lua_setglobal(L, "_episodeBootImage");
        
        lua_pushnumber(L, gEpisodeSettings.episodeBootSoundDelay);
        lua_setglobal(L, "_episodeDelaySetting");

        if (luaL_loadbuffer(L, mainCode.c_str(), mainCode.length(), "=bootscreen.lua"))
        {
            MessageBoxA(NULL, lua_tostring(L, -1), "LunaLua Boot Screen Screen Syntax Error", MB_OK | MB_ICONWARNING);
            return nullptr;
        }
        if (lua_pcall(L, 0, 0, 0))
        {
            MessageBoxA(NULL, lua_tostring(L, -1), "LunaLua Boot Screen Screen Critical Error", MB_OK | MB_ICONWARNING);
            return nullptr;
        }
    }
    if (L == nullptr) return nullptr;
    
    lua_pushboolean(L, false);
    lua_setglobal(L, "_bootScreenComplete");

    lua_getglobal(L, "init");
    if (lua_pcall(L, 0, 0, 0))
    {
        MessageBoxA(NULL, lua_tostring(L, -1), "LunaLua Boot Screen Error", MB_OK | MB_ICONWARNING);
    }
    
    return L;
}

static void bootScreenPlaySFX()
{
    std::wstring path;
    if(gEpisodeSettings.episodeBootSoundID == -1)
    {
        // use custom sfx
        path = resolveIfNotAbsolutePath(gEpisodeSettings.episodeBootSoundCustom);

        // load and play the sound
        Mix_Chunk* chunk = PGE_Sounds::SND_OpenSnd(WStr2Str(path).c_str());
        if (chunk)
        {
            Mix_PlayChannelVol(-1, chunk, 0, MIX_MAX_VOLUME);
        }
    }
    else if(gEpisodeSettings.episodeBootSoundID > 0)
    {
        std::string sfxAlias = "sound" + std::to_string(gEpisodeSettings.episodeBootSoundID);
        MusicManager::play(sfxAlias);
    }
}

void LunaLuaBootSystemRun()
{
    auto L = bootScreenGetLuaState();

    do
    {
        Renderer::Get().StartFrameRender();
        Renderer::Get().StartCameraRender(1);

        // Set camera 0 (primary framebuffer)
        std::shared_ptr<GLEngineCmd_SetCamera> cmd = std::make_shared<GLEngineCmd_SetCamera>();
        cmd->mIdx = 0;
        cmd->mX = 0;
        cmd->mY = 0;
        g_GLEngine.QueueCmd(cmd);
        
        if (L != nullptr) {
            lua_getglobal(L, "onDraw");
            if (lua_pcall(L, 0, 0, 0))
            {
                MessageBoxA(NULL, lua_tostring(L, -1), "LunaLua Boot Screen Error", MB_OK | MB_ICONWARNING);
                gDidBootScreen = true;
            }
            lua_getglobal(L, "_bootScreenComplete");
            if (lua_toboolean(L, -1)) {
                gDidBootScreen = true;
            }
            lua_pop(L, 1);
        } else {
            gDidBootScreen = true;
        }

        Renderer::Get().RenderBelowPriority(DBL_MAX);

        g_GLEngine.EndFrame(NULL, true);

        Renderer::Get().EndFrameRender();
    }
    while(!gDidBootScreen);
}
