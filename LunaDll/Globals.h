//*** Globals.h - It has some globals in it ***
#ifndef globals_hhhhhh
#define globals_hhhhhh

#ifndef __MINGW32__
#pragma warning(disable: 4731)
#pragma warning(disable: 4800)
#pragma warning(disable: 4996) //localtime
#endif
#include <string>
#include <atomic>
#include <cstdint>
#include <mutex>
#include "LevelCodes/LevelCodes.h"
#include "Rendering/Rendering.h"
#include "Autocode/AutocodeManager.h"
#include "CustomSprites/CSpriteManager.h"
#include "CellManager/CellManager.h"
#include "UserSaves/UserSaving.h"
#include "MciEmulator/mciEmulator.h"
#include "HardcodedGraphics/HardcodedGraphicsManager.h"
#include "LuaMain/LunaLuaMain.h"
#include "GameConfig/GameAutostart.h"
#include "Misc/FreeImageUtils/FreeImageInit.h"
#include "GameConfig/GeneralLunaConfig.h"
#include "EventStateMachine.h"
#include "Input/LunaGameController.h"

class RenderOverrideManager;

#include "Defines.h"

#ifndef __MINGW32__
#pragma comment (lib, "msimg32.lib")
#endif

struct StartupEpisodeSettings
{
    bool enabled;
    std::wstring wldPath;
    int players;
    int character1;
    int character2;
    int saveSlot;
    bool canPlaySFXOnStartup;

    StartupEpisodeSettings() :
        enabled(false), wldPath(), players(1),
        character1(1), character2(2), saveSlot(0),
        canPlaySFXOnStartup(false)
    {
    }
};

struct StartupSettings
{
    bool patch;
    bool game;
    bool lvlEditor;
    bool frameskip;
    bool noSound;
    bool debugger;
    bool logger;
    bool newLauncher;
    bool console;
    bool waitForIPC;
    volatile bool currentlyWaitingForIPC;
    bool oldLvlLoader;
    bool softwareGL;
    bool forceHardGL;
    bool runWhenUnfocused;
    bool sendIPCReady;
    bool noBootSound;
    std::wstring levelTest;
    StartupEpisodeSettings epSettings;

    StartupSettings() :
        patch(false), game(false), lvlEditor(false), frameskip(false), noSound(false), debugger(false),
        logger(false), newLauncher(false), console(false), waitForIPC(false), currentlyWaitingForIPC(false),
        oldLvlLoader(false), softwareGL(false), forceHardGL(false), runWhenUnfocused(false), sendIPCReady(false),
        noBootSound(false), epSettings(), levelTest(L"")
    {
    }
};

struct EpisodeSettings
{
    std::wstring episodeDirectory;
    
    bool usingCustomSplash;
    std::wstring episodeBootImage;

    std::wstring episodeBootSoundCustom;
    int episodeBootSoundID;
    int episodeBootSoundDelay;
    
    bool useLegacyBootScreen;
    bool displayOriginalCredits;
    bool hideAllCreditLines;
    
    EpisodeSettings() :
        episodeDirectory(L""),
        usingCustomSplash(false), episodeBootImage(L""),
        episodeBootSoundCustom(L""), episodeBootSoundID(29), episodeBootSoundDelay(0),
        useLegacyBootScreen(false), displayOriginalCredits(false), hideAllCreditLines(false)
    {
    }
};

struct SMBXHUDSettings {
    bool              skip; // Skip the whole HUD drawing
    WORLD_HUD_CONTROL overworldHudState;
    bool              skipStarCount;
};

extern HINSTANCE	gHInstance;

/// Global main window state
extern HWND gMainWindowHwnd;
extern bool gMainWindowFocused;

/// Global settings
extern bool            gLunaEnabled;
extern bool            gPrintErrorsToScreen;
extern bool            gIsOverworld;
extern bool            gHook_SkipTestMsgBox;
extern bool            gAutostartRan;
extern SMBXHUDSettings gSMBXHUDSettings;

extern bool            gRenderBGOFlag;
extern bool            gRenderSizableFlag;
extern bool            gRenderBackgroundFlag;
extern bool            gRenderPlayerFlag;

extern bool            gOnStartRan;

// Settings for glitch fixes
extern bool            gDisablePlayerFilterBounceFix;

// Other gameplay settings
extern bool            gRightClickPaste;
extern bool            gLavaIsWeak;
extern bool            gLavaIsSafe;
extern bool            gRunWhenUnfocused;
extern bool            gDisablePlayerKeys;
extern bool            gDisablePlayerMovementAboveThree;

// Set to true when returning from gameover screen, read by lua to handle gameover-related stuff
extern bool            gDidGameOver;
// Flag for booting an episode
extern bool            gDidBootScreen;

extern StartupSettings gStartupSettings;
extern EpisodeSettings gEpisodeSettings;

/// General use globals - These are all defined in Globals.cpp ///
extern int		gFrames;

extern int		gLastDownPress;
extern int		gDownTapped;
extern int		gLastUpPress;
extern int		gUpTapped;
extern int		gLastLeftPress;
extern int		gLeftTapped;
extern int		gLastRightPress;
extern int		gRightTapped;

extern int		gLastJumpPress;
extern int		gJumpTapped;
extern int		gLastRunPress;
extern int		gRunTapped;

extern BYTE     gKeyState[9][256];

extern HDC		ghMemDC;		// General-use screen-compatible DC
extern HBITMAP	ghGeneralDIB;	// General-use screen-sized DIB
extern DWORD*	gpScreenBits;	// Pointer to screen bits for general use DIB

// Mouse cursor
extern HCURSOR  gCustomCursor;
extern bool     gCustomCursorHide;

// Key status
extern short	gNumpad4;
extern short	gNumpad8;
extern short	gNumpad2;
extern short	gNumpad6;

// Raw player keymap
extern KeyMap   gRawKeymap[4];

// Esc pressed tracking for runtimeHookLevelPauseCheck
extern bool     gEscPressed;
extern bool     gEscPressedRegistered;

// Test mode pause note
extern bool     gIsTestModePauseActive;

// Level init
extern LvlEnum	gLevelEnum;

// Misc
extern AutocodeManager		gAutoMan;
extern CSpriteManager		gSpriteMan;
extern CellManager			gCellMan;
extern SavedVariableBank	gSavedVarBank;
extern MciEmulator			gMciEmulator;
extern HardcodedGraphicsManager gGraphManager;
extern FreeImageInit        gFreeImgInit;
extern GeneralLunaConfig    gGeneralConfig;
extern LunaGameControllerManager gLunaGameControllerManager;

extern CLunaLua				gLunaLua;

extern FILE* conout;

// Paths
extern std::string  gAppPathANSI;
extern std::string  gAppPathUTF8;
extern std::wstring gAppPathWCHAR;
extern std::string  gCwdPathANSI;
extern std::string  gCwdPathUTF8;
extern std::wstring gCwdPathWCHAR;

// Message boxes with printf-like syntax
void printBoxA(const char *fmt, ...);
void printBoxW(const wchar_t *fmt, ...);

/// HELPER MACROS ///
/*
if(!hRunProc){
std::string errMsg = "Failed to load 'run' in the Launcher dll D:!\nIs Lunadll.dll or LunadllNewLauncher.dll different versions?\nError code:";
errMsg += std::to_string((long long)GetLastError());
MessageBoxA(NULL, errMsg.c_str(), "Error", NULL);
FreeLibrary(newLauncherLib);
newLauncherLib = NULL;
return;
}
*/
#define GL_PROC_CHECK(procHandle, procName, moduleHandle, moduleName) \
    if(!procHandle){\
        std::string errMsg = "Failed to load 'procName' in moduleName D:!\nIs Lunadll.dll or moduleName different versions?\nError code:";\
        errMsg += std::to_string((long long)GetLastError());\
        MessageBoxA(NULL, errMsg.c_str(), "Error", 0);\
        FreeLibrary(moduleHandle);\
        moduleHandle = NULL;\
        return;\
    }


#endif

// Editor IPC Entities
extern std::string gEditorPlacedItem;
extern std::mutex g_editorIPCMutex;

extern double soundEffectCount;
extern bool canUseSEEModFeatures;

// Episode loading
extern Characters gPlayerStoredCharacters[];
extern bool gEpisodeLoadedOnBoot;
extern bool gEngineStarted;

extern int gUnfocusTimer;
extern int gFocusTimer;
