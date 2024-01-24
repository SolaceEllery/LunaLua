#include <string>
#include <memory>
#include <luabind/adopt_policy.hpp>
#include <luabind/out_value_policy.hpp>

#include "EpisodeMain.h"

#include "../../version.h"
#include "../../Globals.h"
#include "../../GlobalFuncs.h"
#include "../../SMBXInternal/Level.h"
#include "../../Misc/MiscFuncs.h"
#include "../../SMBXInternal/PlayerMOB.h"
#include "../../SMBXInternal/NPCs.h"
#include "../../SMBXInternal/BGOs.h"
#include "../../SMBXInternal/Animation.h"
#include "../../SMBXInternal/Overworld.h"

#include "../../Rendering/FrameCapture.h"

#include "../../LuaMain/LuaHelper.h"
#include "../../LuaMain/LuaProxy.h"
#include "../../LuaMain/LuaProxyComponent/LuaProxyAudio.h"
#include "../../libs/luasocket/luasocket.h"
#include "../../libs/luasocket/mime.h"
#include "../../SdlMusic/MusicManager.h"
#include "../../Rendering/LunaImage.h"
#include "../../Rendering/ImageLoader.h"
#include "../../Misc/RuntimeHook.h"
#include "../../Input/MouseHandler.h"

#include "../../Misc/LoadScreen.h"
#include "../../LuaMain/LunaPathValidator.h"

#include "../../Misc/CollisionMatrix.h"
#include "../../FileManager/SMBXFileManager.h"

extern PlayerMOB* getTemplateForCharacterWithDummyFallback(int id);
extern "C" void __cdecl LunaLuaSetGameData(const char* dataPtr, int dataLen);

// Patch to allow exiting the pause menu. Apply when the vanilla pause/textbox
// should be instantly exited always. Unapply when this should not be the case.
static auto exitPausePatch = PATCH(0x8E6564).NOP().NOP().NOP().NOP().NOP().NOP();

EpisodeMain::EpisodeMain() :
    canExecuteViaLua(false),
    currentOverworldLvl(0)
{}

EpisodeMain::~EpisodeMain() {}

// The big one. This will load an episode anywhere in the engine. This is also used when booting the engine.
void EpisodeMain::LaunchEpisode(std::wstring wldPath, int saveSlot, int playerCount, Characters firstCharacter, Characters secondCharacter, bool suppressSound)
{
    // make sure this is false before we begin
    gIsOnMainMenu = false;

    //--ElseIf .Jump = True Or .Start = True Or (GetKeyState(vbKeySpace) And KEY_PRESSED) Or (GetKeyState(vbKeyReturn) And KEY_PRESSED) Or MenuMouseClick = True Then (line 4945)--

    // put the world together
    std::wstring fullPath = resolveCwdOrWorldsPath(wldPath);

    // make sure we also get the path without the wld file
    std::string fullPathStr = WStr2Str(fullPath);
    std::string fullPathNoWorldPth = splitFilenameFromPath(fullPathStr);
    std::string fullPathNoWorldPthWithEndSlash = fullPathNoWorldPth + "\\";

    // check to see if non-default Windows ANSI code page stuff is there, otherwise don't load the entire episode if booting, else if after booted, continue the game like usual
    std::wstring nonAnsiCharsEpisode = GetNonANSICharsFromWStr(Str2WStr(fullPathNoWorldPthWithEndSlash));
    if (!nonAnsiCharsEpisode.empty())
    {
        std::wstring path = L"The episode path has characters which are not compatible with the system default Windows ANSI code page. This is not currently supported. Please rename or move your episode folder.\n\nUnsupported characters: " + nonAnsiCharsEpisode + L"\n\nPath:\n" + fullPath;
        MessageBoxW(0, path.c_str(), L"SMBX does not support episode path", MB_ICONERROR);
        _exit(1);
    }

    // make sure the game unpauses and Lua is gone before starting after the episode has loaded successfully after boot
    if(gEpisodeLoadedOnBoot)
    {
        gLunaLua.exitContext();
        exitPausePatch.Apply();

        gCachedFileMetadata.purge();
        
        std::string worldName = findNameFromEpisodeWorldPath(WStr2Str(wldPath));
        
        GameAutostart autoStartEpisode;
        autoStartEpisode.setSelectedEpisode(worldName);
        autoStartEpisode.setSelectedEpisodePath(fullPath);
        autoStartEpisode.setSaveSlot(saveSlot);
    }

    // show loadscreen
    LunaLoadScreenStart();

    // setup SFXs
    native_setupSFX();

    // setup the world to load for later in this function
    VB6StrPtr pathVb6 = WStr2Str(fullPath);
    
    // specify the save slot, the fulldir, and the menu level for the wld file
    SMBXWorldFileBase::PopulateEpisodeList();
    GM_CUR_MENULEVEL = findEpisodeIDFromWorldFileAndPath(WStr2Str(fullPath)); // this NEEDS to be set, otherwise the engine will just crash loading the episode

    // clear gamedata
    LunaLuaSetGameData(0, 0);

    //--BEGIN MAIN RECODE--

    // implement player count
    GM_PLAYERS_COUNT = playerCount; //--numPlayers = MenuMode / 10 (line 4947)--
    
    // apply templates

    /*
        --
            For A = 1 To numCharacters (line 4948)
                SavedChar(A) = blankPlayer (line 4949)
                SavedChar(A).Character = A (line 4950)
                SavedChar(A).State = 1 (line 4951)
            Next A
        --
    */

    For(i, 1, GM_PLAYERS_COUNT)
    {
        auto p = Player::Get(i);
        auto t = getTemplateForCharacterWithDummyFallback(static_cast<int>(p->Identity));
        if (t != nullptr) {
            memcpy(p, t, sizeof(PlayerMOB));
        }
    }

    // use the character variables that were specified
    For(i, 1, GM_PLAYERS_COUNT)
    {
        auto p = Player::Get(i);

        // if we have any blocked characters, don't use them and instead specify whatever is not blocked (Not compatible with X2 characters, but they're a mess in basegame so oh well)
        checkBlockedCharacterFromWorldAndReplaceCharacterIfSo(i);

        // implement missing player values before loading-- the save file
        p->CurrentPowerup = 1; //--Player(1/2).State (line 4953/4964)--
        p->MountType = 0; //--Player(1/2).Mount (line 4954/4965)--
        p->Identity = static_cast<Characters>(1); //--Player(1/2).Character = 1 (line 4955/4966)--
        p->PowerupBoxContents = 0; //--Player(1/2).HeldBonus = 0 (line 4956/4967)--
        p->TakeoffSpeed = 0; //--Player(1/2).CanFly = False (line 4957/4968)--
        p->CanFly = 0; //--Player(1/2).CanFly2 = False (line 4958/4969)--
        p->TailswipeTimer = 0; //--Player(1/2).TailCount = 0 (line 4959/4970)--
        p->YoshiHasEarthquake = 0; //--Player(1/2).YoshiBlue = False (line 4960/4971)--
        p->YoshiHasFireBreath = 0; //--Player(1/2).YoshiRed = False (line 4961/4972)--
        p->YoshiHasFlight = 0; //--Player(1/2).YoshiYellow = False (line 4962/4973)--
        p->Hearts = 0; //--Player(1/2).Hearts = 0 (line 4963/4974)--
    }

    auto p1 = Player::Get(1);

    // implement the 1st player's character
    if(GM_PLAYERS_COUNT >= 1)
    {
        // checks to make sure that the character can be selected or not
        if(firstCharacter != static_cast<Characters>(0) && firstCharacter <= static_cast<Characters>(5))
        {
            p1->Identity = firstCharacter;
        }
        else
        {
            p1->Identity = static_cast<Characters>(1);
        }
    }

    // implement the 2nd player's character
    if(GM_PLAYERS_COUNT >= 2)
    {
        For(i, 2, GM_PLAYERS_COUNT)
        {
            // get any player above 2
            auto p2 = Player::Get(i);

            // checks to make sure that the character can be selected or not
            if(secondCharacter != static_cast<Characters>(0) && secondCharacter <= static_cast<Characters>(5))
            {
                p2->Identity = secondCharacter;
            }
            else
            {
                p2->Identity = static_cast<Characters>(2);
            }
        }
    }

    // we'll probably get more than 3 players loading on boot if specified on the command prompt, so this needs to exist
    if(GM_PLAYERS_COUNT >= 3)
    {
        For(i, 3, GM_PLAYERS_COUNT)
        {
            auto p = Player::Get(i);
            p->Identity = Player::Get(1)->Identity;
        }
    }
    
    if(gEpisodeLoadedOnBoot) // do this too if an episode is already loaded
    {
        // restore characters if booted already
        For(i, 1, GM_PLAYERS_COUNT)
        {
            auto p = Player::Get(i);

            // restore this player's character
            p->Identity = gPlayerStoredCharacters[min(i, 4)-1];

            // if we have any blocked characters, don't use them and instead specify whatever is not blocked (Not compatible with X2 characters, but they're a mess in basegame so oh well)
            checkBlockedCharacterFromWorldAndReplaceCharacterIfSo(i);
        }
    }

    // replicating code from 1.3 cause why not
    GM_CUR_MENUCHOICE = saveSlot - 1;

    // implement missing values before loading the save file
    GM_CUR_SAVE_SLOT = GM_CUR_MENUCHOICE + 1; //--selSave = MenuCursor + 1 (line 4983)--
    GM_STAR_COUNT = 0; //--numStars = 0 (4984)--
    GM_COINS = 0; //--Coins = 0 (4985)--
    GM_UNK_B2C8E4 = 0; //--Score = 0 (line 4986)--
    GM_PLAYER_LIVES = 3; //--Lives = 3 (line 4987)--
    
    /*
        skipping these cause lunadll handles this stuff instead

        --
            BitBlt myBackBuffer, 0, 0, ScreenW, ScreenH, 0, 0, 0, vbWhiteness (line 4990)
            BitBlt frmMain.hdc, 0, 0, frmMain.ScaleWidth, frmMain.ScaleHeight, 0, 0, 0, vbWhiteness (line 4991)
        --
    */
    
    //load the map
    GM_EPISODE_MODE = COMBOOL(true); //--LevelSelect = True (line 4988)--
    GM_LEVEL_MODE = COMBOOL(false); //--GameMenu = False (line 4989)--

    // stop music
    native_stopMusic(); //--StopMusic (line 4992)--
    
    /*
        skipping these cause lunadll handles this stuff instead

        --
            DoEvents (line 4993)
            Sleep 500 (line 4994)
        --
    */
    // load the world data
    native_loadWorld(&pathVb6); //--OpenWorld SelectWorld(selWorld).WorldPath & SelectWorld(selWorld).WorldFile (line 4995)--

    // play the world loaded sfx if suppressSound is false
    if(!suppressSound)
    {
        if(gStartupSettings.epSettings.canPlaySFXOnStartup)
        {
            short soundID = 28;
            native_playSFX(&soundID); //--PlaySound 29 (line 4946) [i modified it to play 28 instead, which is the level select SFX]--
        }
    }

    // load the save file data
    if (GM_CUR_SAVE_SLOT >= 0 && saveFileExists()) //--If SaveSlot(selSave) >= 0 Then (line 4996)--
    {
        // blank out intro filename if the episode already has a save file and the intro was already played
        if(GM_HUB_STYLED_EPISODE == 0) //--If NoMap = False Then StartLevel = "" (line 4997)--
        {
            GM_WORLD_INTRO_FILENAME = "";
        }

        native_loadGame(); //--LoadGame (line 4998)--
    }

    // get if the illparkwhereiwant cheat is active
    if(GM_WORLD_UNLOCK == -1) //--If WorldUnlock = True Then (line 5000)--
    {
        // get all paths
        For(i, 1, GM_PATH_COUNT) //--For A = 1 To numWorldPaths (line 5001)--
        {
            /*
                --
                    With tempLocation (line 5003)
                        .X = .X + 4 (line 5004)
                        .Y = .Y + 4 (line 5005)
                        .Width = .Width - 8 (line 5006)
                        .Height = .Height - 8 (line 5007)
                    End With (line 5008)
                --
            */
            SMBXPath::Get(i)->momentum.x = SMBXPath::Get(i)->momentum.x + 4;
            SMBXPath::Get(i)->momentum.y = SMBXPath::Get(i)->momentum.y + 4;
            SMBXPath::Get(i)->momentum.width = SMBXPath::Get(i)->momentum.width - 8;
            SMBXPath::Get(i)->momentum.height = SMBXPath::Get(i)->momentum.height - 8;

            // set to active
            SMBXPath::Get(i)->visible = COMBOOL(true); //--WorldPath(A).Active = True (line 5009)--

            // now get sceneries
            For(j, 1, GM_SCENERY_COUNT) //--For B = 1 To numScenes (line 5010)--
            {
                // check the collision of paths and sceneries
                if(CheckCollision(SMBXPath::Get(i)->momentum, SMBXScenery::Get(j)->momentum)) //--If CheckCollision(tempLocation, Scene(B).Location) Then Scene(B).Active = False (line 5011)--
                {
                    // make any scenery if collided invisible if true
                    SMBXScenery::Get(j)->field_32 = COMBOOL(false);
                }
            }
        }

        // now get world levels
        For(i, 1, GM_LEVEL_COUNT) //--For A = 1 To numWorldLevels (line 5014)--
        {
            // make them visible
            WorldLevel::Get(i)->visible = COMBOOL(true); //--WorldLevel(A).Active = True (line 5015)--
        }
    }
    
    /*
        --
                Next A (line 5016)
            End If (line 5017)
        --
    */

    // init SetupPlayers
    native_initLevelEnv(); //--SetupPlayers (line 5018)--

    if((GM_WORLD_INTRO_FILENAME != GM_STR_NULL && !saveFileExists()) || (GM_HUB_STYLED_EPISODE == -1)) //--If StartLevel <> "" Then-- (line 5019)
    {
        // load the autoboot level from the episode if we're starting it for the first time, or the hub level if it's a hub-styled episode
        std::string fullPathAndAutobootLvl = fullPathNoWorldPthWithEndSlash + (std::string)GM_WORLD_INTRO_FILENAME;
        VB6StrPtr fullPathAndAutobootLvlVB6 = fullPathAndAutobootLvl;
        GM_EPISODE_MODE = COMBOOL(false); //--LevelSelect = False (line 5022)--
        native_loadLevel(&fullPathAndAutobootLvlVB6); //--OpenLevel SelectWorld(selWorld).WorldPath & StartLevel (line 5028)
    }

    // reset cheat status
    GM_CHEATED = COMBOOL(false);

    // reset checkpoints
    GM_STR_CHECKPOINT = "";

    // make sure that lunadll knows the game loaded on boot, so that loadEpisode can know
    if(!gEpisodeLoadedOnBoot)
    {
        gEpisodeLoadedOnBoot = true;
    }

    exitPausePatch.Unapply();

    // hide loadscreen
    LunaLoadScreenKill();
    
    //--End If (line 5031)--

    //--END MAIN RECODE--
}

// This will load a level from the current episode anywhere in the engine (Even the world map!)
void EpisodeMain::LoadLevel(std::string levelName, int warpIdx, std::string episodeName, int overworldLvlID, bool suppressSound)
{
    // make sure this is false before we begin
    gIsOnMainMenu = false;

    // get the full dir as a string, combine the level name and directory, and turn the other string into a VB6StrPtr, for later
    std::string fullDir = (std::string)GM_FULLDIR;
    std::string fullDirWithFilename = fullDir + levelName;
    VB6StrPtr fullDirWithFilenameVB6 = fullDirWithFilename;

    if(episodeName != "")
    {
        
    }

    // make sure it knows the file exists
    if(fileExists(Str2WStr(fullDirWithFilename))) //--If Dir(SelectWorld(selWorld).WorldPath & WorldLevel(A).FileName) <> "" Then (line 7263)--
    {
        // skip to line 7262, the parts before that pertain to warps...
        if(levelName != "" && levelName != ".lvl" && levelName != ".lvlx") //--If WorldLevel(A).FileName <> "" And WorldLevel(A).FileName <> ".lvl" Then (line 7262)--
        {
            // make sure the game unpauses and Lua is gone before starting a level
            exitPausePatch.Apply();

            gLunaLua.exitContext();
            gCachedFileMetadata.purge();

            // start with WorldLoop on modMain.bas, line 7244

            // show loadscreen
            LunaLoadScreenStart();
            
            // if warpIdx is greater than or equal to 0, apply the warp idx
            if(warpIdx >= 0)
            {
                GM_NEXT_LEVEL_WARPIDX = warpIdx; //--StartWarp = WorldLevel(A).StartWarp (line 7264)--
            }

            // stop the music
            native_stopMusic(); //--StopMusic (line 7265)--

            if(gIsOverworld)
            {
                //cleanup world
                native_cleanupWorld();
            }

            // play the sound if not suppressed
            if(!suppressSound)
            {
                short soundID = 28;
                native_playSFX(&soundID); //--PlaySound 28 (line 7266)--
            }
            
            if(gIsOverworld)
            {
                if(overworldLvlID >= 1)
                {
                    GM_OVERWORLD_CUR_LVL = overworldLvlID;
                }
                else
                {
                    GM_OVERWORLD_CUR_LVL = 1;
                }
            }

            // make the world map false
            GM_EPISODE_MODE = COMBOOL(false); //--LevelSelect = False (line 7269)--

            // clean up the level
            native_cleanupLevel(); //--ClearLevel (line 7271)--

            // make sure we aren't in overworld anymore if we were
            if(gIsOverworld)
            {
                gIsOverworld = false;
            }
            
            // apply the dir and filename, and load it!
            native_loadLevel(&fullDirWithFilenameVB6); //--OpenLevel SelectWorld(selWorld).WorldPath & WorldLevel(A).FileName (line 7273)--
            
            // unapply force pause-exit patch
            exitPausePatch.Unapply();

            // hide loadscreen
            LunaLoadScreenKill();

        } //--End If (line 7275)--
        // that's the end of WorldLoop.bas stuff
    }
}

void EpisodeMain::preLoadMainMenu()
{
    EpisodeMain episodeMainFunc;
    // get the full dir as a string, combine the level name and directory, and turn the other string into a VB6StrPtr, for later
    std::string fullDir = gAppPathUTF8 + "\\";
    std::string fullDirWithFilename = fullDir + "intro.lvl";
    std::string fullDirWithFilenameAlt = fullDir + "intro.lvlx";

    // check and see if intro.lvl exists
    if(fileExists(Str2WStr(fullDirWithFilename)))
    {
        episodeMainFunc.loadMainMenu(std::string fullDirWithFilename);
    }
    // else just use intro.lvlx
    else if(fileExists(Str2WStr(fullDirWithFilenameAlt)))
    {
        episodeMainFunc.loadMainMenu(std::string fullDirWithFilenameAlt);
    }
    // or if nothing exists, error and exit
    else
    {
        std::string msg = "There is no intro.lvl, or intro.lvlx. Unless you're booting an episode, they will be needed in order to load the alt launcher. Please press OK so that the game can close.";
        MessageBoxA(gMainWindowHwnd, msg.c_str(), "Error", MB_ICONWARNING | MB_OK);
        _exit(0);
    }
}

void EpisodeMain::loadMainMenu(std::string mainMenuLvl)
{
    EpisodeMain episodeMainFunc;
    VB6StrPtr fullDirWithFilenameVB6 = mainMenuLvl;

    // make sure it knows the file exists
    if(fileExists(Str2WStr(fullDirWithFilename)))
    {
        // skip to line 7262, the parts before that pertain to warps...
        if(mainMenuLvl != "" && mainMenuLvl != ".lvl" && mainMenuLvl != ".lvlx")
        {
            // make sure the game unpauses and Lua is gone before starting a level
            exitPausePatch.Apply();

            if(gEpisodeLoadedOnBoot)
            {
                gLunaLua.exitContext();
                gCachedFileMetadata.purge();

                if(gIsOverworld)
                {
                    gIsOverworld = false;
                }
            }

            // show loadscreen
            LunaLoadScreenStart();
            
            // apply the warp idx
            GM_NEXT_LEVEL_WARPIDX = 0;

            // stop the music
            native_stopMusic();

            // make the world map false
            GM_EPISODE_MODE = COMBOOL(false);

            // clean up the level and world
            native_cleanupLevel();
            native_cleanupWorld();
            
            // apply the dir and filename, and load it!
            native_loadLevel(&fullDirWithFilenameVB6);
            
            // unapply force pause-exit patch
            exitPausePatch.Unapply();

            // we're on the main menu, so this is true
            gIsOnMainMenu = true;

            // hide loadscreen
            LunaLoadScreenKill();

            // start the main menu lvl
            episodeMainFunc.onStartMainMenu()

        }
        // that's the end of that
    }
}

void EpisodeMain::onStartMainMenu()
{
    // reset battleintro and battleoutro
    GM_MARIO_VS_LUIGI_T = 0;
    GM_WINS_T = 0;

    // reset cheat status
    GM_CHEATED = COMBOOL(false);

    // reset checkpoints
    GM_STR_CHECKPOINT = "";

    // reset cheat string
    GM_INPUTSTR_BUF_PTR = "";

    // set camera control to 2 (Follow all players, used for most of the supermario# cheats)
    GM_CAMERA_CONTROL = 2;
}
