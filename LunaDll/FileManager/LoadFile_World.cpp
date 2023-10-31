#include <future>
#include <chrono>
#include <thread>
#include <fmt/fmt_format.h>

#include "../Defines.h"
#include "../Globals.h"
#include "../GlobalFuncs.h"

#include "../libs/PGE_File_Formats/file_formats.h"

#include "../SMBXInternal/Overworld.h"
#include "../SMBXInternal/Path.h"
#include "../SMBXInternal/WorldLevel.h"
#include "../SMBXInternal/Scenery.h"
#include "../SMBXInternal/Tile.h"
#include "../SMBXInternal/MusicBox.h"
#include "../../Rendering/ImageLoader.h"

#include "CustomParamStore.h"

// used to open up initial path upon starting the world
void setPathsToVisible(Momentum* loc) {
    // in each direction...
    for (int i = 1; i <= 4; i++)
    {
        // calculate bounds to check for collisions
        float checkX1 = loc->x + 4;
        float checkY1 = loc->y + 4;
        switch (i)
        {
        case 1: checkX1 += loc->width; break;
        case 2: checkY1 += loc->height; break;
        case 3: checkX1 -= 32; break;
        case 4: checkY1 -= 32; break;
        }
        float checkX2 = checkX1 + ((i == 2 || i == 4) ? loc->width  : 32) - 8;
        float checkY2 = checkY1 + ((i == 1 || i == 3) ? loc->height : 32) - 8;
        // check ALL paths for intersection
        for (int j = 0; j < SMBXPath::Count(); j++)
        {
            SMBXPath* obj = SMBXPath::Get(j);
            if (obj->visible) continue;
            if (checkX2 <= obj->momentum.x) continue;
            if (checkY2 <= obj->momentum.y) continue;
            if (obj->momentum.x + obj->momentum.width <= checkX1) continue;
            if (obj->momentum.y + obj->momentum.height <= checkY1) continue;
            // start the path as visible
            obj->visible = true;
            // show paths relative to this path
            setPathsToVisible(&obj->momentum);
            // hide scenery touching this path
            float sceneCheckX1 = obj->momentum.x + 4;
            float sceneCheckY1 = obj->momentum.y + 4;
            float sceneCheckX2 = sceneCheckX1 + obj->momentum.width - 8;
            float sceneCheckY2 = sceneCheckY1 + obj->momentum.height - 8;
            // check ALL scenes for intersection
            for (int k = 0; k < SMBXScenery::Count(); k++)
            {
                SMBXScenery* scene = SMBXScenery::Get(k);
                if (sceneCheckX2 <= scene->momentum.x) continue;
                if (sceneCheckY2 <= scene->momentum.y) continue;
                if (scene->momentum.x + scene->momentum.width <= sceneCheckX1) continue;
                if (scene->momentum.y + scene->momentum.height <= sceneCheckY1) continue;
                scene->visible = false;
            }
        }
        // check ALL levels for intersection
        for (int j = 0; j < WorldLevel::Count(); j++)
        {
            WorldLevel* obj = WorldLevel::Get(j);
            if (obj->visible) continue;
            if (checkX2 <= obj->momentum.x) continue;
            if (checkY2 <= obj->momentum.y) continue;
            if (obj->momentum.x + obj->momentum.width <= checkX1) continue;
            if (obj->momentum.y + obj->momentum.height <= checkY1) continue;
            // start the level as visible
            obj->visible = true;
            // show paths relative to this level
            setPathsToVisible(&obj->momentum);
        }
    }
}

void LunaLua_loadWorldFile(WorldData& outData, std::wstring fullPath, bool isValid)
{
    std::vector<std::string> limitWarnings;
    std::vector<std::string> nearLimitWarnings;

    native_cleanupWorld();

    size_t slashPos = fullPath.find_last_of(L"\\/");
    GM_FULLDIR = fullPath.substr(0, slashPos + 1);
    GM_LVLFILENAME_PTR = fullPath.substr(slashPos + 1, fullPath.length()-(slashPos+1));

    //ImageLoader::Run(); also called later

    GM_TILE_COUNT = 0;
    GM_SCENERY_COUNT = 0;
    GM_LEVEL_COUNT = 0;
    GM_PATH_COUNT = 0;
    GM_MUSICBOX_COUNT = 0;
    
    // read 1.3 locked chars
    GM_WORLD_LOCKED_CHARACTERS_PTR[1] = COMBOOL(outData.nocharacter1);
    GM_WORLD_LOCKED_CHARACTERS_PTR[2] = COMBOOL(outData.nocharacter2);
    GM_WORLD_LOCKED_CHARACTERS_PTR[3] = COMBOOL(outData.nocharacter3);
    GM_WORLD_LOCKED_CHARACTERS_PTR[4] = COMBOOL(outData.nocharacter4);
    GM_WORLD_LOCKED_CHARACTERS_PTR[5] = COMBOOL(outData.nocharacter5);
    // read other locked chars
    // TODO: this
    /*for (int i = 0; i < outData.nocharacter.size(); i++) {
        auto lock = outData.nocharacter[i];

    }*/

    GM_WORLD_AUTOSTART_LVLNAME_PTR = outData.IntroLevel_file;
    GM_WORLD_IS_HUB_EPISODE = COMBOOL(outData.HubStyledWorld);
    GM_WORLD_RESTART_LVL_ON_DEATH = COMBOOL(outData.restartlevel);
    GM_WORLD_TOTAL_STARS = COMBOOL(outData.stars);
    // credits:
    GM_WORLD_CREDITS_ARRAY[0] = outData.author1;
    GM_WORLD_CREDITS_ARRAY[1] = outData.author2;
    GM_WORLD_CREDITS_ARRAY[2] = outData.author3;
    GM_WORLD_CREDITS_ARRAY[3] = outData.author4;
    GM_WORLD_CREDITS_ARRAY[4] = outData.author5;

    // LOAD TILES /////////////////////////////////////////
    int numTiles = outData.tiles.size();
    /*if (numTiles > SMBXTile::MAX_ID)
    {
        limitWarnings.push_back(std::to_string(numTiles) + "/" + std::to_string(SMBXTile::MAX_ID) + " tiles");
        numTiles = SMBXTile::MAX_ID;
    }
    else if (numTiles > (SMBXTile::MAX_ID - SMBXTile::MAX_ID / 20))
    {
        nearLimitWarnings.push_back(std::to_string(numTiles) + "/" + std::to_string(SMBXTile::MAX_ID) + " tiles");
    }*/
    GM_TILE_COUNT = numTiles;
    for (int i = 0; i < numTiles; i++) {
        auto tile = outData.tiles[i];
        auto obj = SMBXTile::Get(i);
        obj->id = tile.id;
        obj->momentum.x = tile.x;
        obj->momentum.y = tile.y;
        obj->momentum.width = tiledef_width[obj->id-1];
        obj->momentum.height = tiledef_height[obj->id-1];
    }

    // LOAD SCENES /////////////////////////////////////////
    int numScenes = outData.scenery.size();
    /*if (numScenes > SMBXScenery::MAX_ID)
    {
        limitWarnings.push_back(std::to_string(numScenes) + "/" + std::to_string(SMBXScenery::MAX_ID) + " scenery");
        numScenes = SMBXScenery::MAX_ID;
    }
    else if (numScenes > (SMBXScenery::MAX_ID - SMBXScenery::MAX_ID / 20))
    {
        nearLimitWarnings.push_back(std::to_string(numScenes) + "/" + std::to_string(SMBXScenery::MAX_ID) + " scenery");
    }*/
    GM_SCENERY_COUNT = numScenes;
    for (int i = 0; i < numScenes; i++) {
        auto scene = outData.scenery[i];
        auto obj = SMBXScenery::Get(i);
        obj->id = scene.id;
        obj->momentum.x = scene.x;
        obj->momentum.y = scene.y;
        obj->momentum.width = scenerydef_width[obj->id-1];
        obj->momentum.height = scenerydef_height[obj->id-1];
        obj->visible = COMBOOL(1);
    }

    // LOAD PATHS /////////////////////////////////////////
    int numPath = outData.paths.size();
    /*if (numPath > SMBXPath::MAX_ID)
    {
        limitWarnings.push_back(std::to_string(numPath) + "/" + std::to_string(SMBXPath::MAX_ID) + " paths");
        numPath = SMBXPath::MAX_ID;
    }
    else if (numPath > (SMBXPath::MAX_ID - SMBXPath::MAX_ID / 20))
    {
        nearLimitWarnings.push_back(std::to_string(numPath) + "/" + std::to_string(SMBXPath::MAX_ID) + " paths");
    }*/
    GM_PATH_COUNT = numPath;
    for (int i = 0; i < numPath; i++) {
        auto path = outData.paths[i];
        auto obj = SMBXPath::Get(i);
        obj->id = path.id;
        obj->momentum.x = path.x;
        obj->momentum.y = path.y;
        obj->momentum.width = 32;
        obj->momentum.height = 32;
    }

    // LOAD LEVELS /////////////////////////////////////////
    int numLevel = outData.levels.size();
    /*if (numLevel > WorldLevel::MAX_ID)
    {
        limitWarnings.push_back(std::to_string(numLevel) + "/" + std::to_string(WorldLevel::MAX_ID) + " levels");
        numLevel = WorldLevel::MAX_ID;
    }
    else if (numLevel > (WorldLevel::MAX_ID - WorldLevel::MAX_ID / 20))
    {
        nearLimitWarnings.push_back(std::to_string(numLevel) + "/" + std::to_string(WorldLevel::MAX_ID) + " levels");
    }*/
    GM_LEVEL_COUNT = numLevel;
    for (int i = 0; i < numLevel; i++) {
        auto level = outData.levels[i];
        auto obj = WorldLevel::Get(i);
        obj->id = level.id;
        obj->momentum.x = level.x;
        obj->momentum.y = level.y;
        obj->momentum.width = 32;
        obj->momentum.height = 32;
        obj->rightExitType  = (ExitType)level.right_exit;
        obj->leftExitType   = (ExitType)level.left_exit;
        obj->topExitType    = (ExitType)level.top_exit;
        obj->bottomExitType = (ExitType)level.bottom_exit;
        obj->isAlwaysVisible = COMBOOL(level.alwaysVisible);
        obj->isPathBackground = COMBOOL(level.pathbg);
        obj->isBigBackground = COMBOOL(level.bigpathbg);
        obj->isGameStartPoint = COMBOOL(level.gamestart);
        obj->levelFileName = level.lvlfile;
        obj->levelTitle = level.title;
        obj->goToX = level.gotox;
        obj->goToY = level.gotoy;
        obj->levelWarpNumber = level.entertowarp;
        obj->visible = obj->isAlwaysVisible;
    }

    // LOAD MUSIC /////////////////////////////////////////
    int numMusic = outData.music.size();
    /*if (numMusic > WorldMusicBox::MAX_ID)
    {
        limitWarnings.push_back(std::to_string(numMusic) + "/" + std::to_string(WorldLevel::MAX_ID) + " music boxes");
        numMusic = WorldLevel::MAX_ID;
    }
    else if (numMusic > (WorldLevel::MAX_ID - WorldLevel::MAX_ID / 20))
    {
        nearLimitWarnings.push_back(std::to_string(numMusic) + "/" + std::to_string(WorldLevel::MAX_ID) + " music boxes");
    }*/
    GM_MUSICBOX_COUNT = numMusic;
    for (int i = 0; i < numMusic; i++) {
        auto music = outData.music[i];
        auto obj = SMBXMusicbox::Get(i);
        obj->id = music.id;
        obj->momentum.x = music.x;
        obj->momentum.y = music.y;
        obj->momentum.width = 32;
        obj->momentum.height = 32;
    }

    // UNIMPLEMENTED FIELDS:
    /*
    bool restrictSinglePlayer = false;
    bool restrictCharacterSwitch = false;
    bool restrictSecureGameSave = false;
    bool disableEnterScreen = false;
    bool cheatsPolicy = CHEATS_DENY_IN_LIST;
    PGESTRINGList cheatsList;
    int     saveResumePolicy = SAVE_RESUME_AT_WORLD_MAP;
    bool    saveAuto = false;
    bool    saveLocker = false;
    PGESTRING saveLockerEx = "";
    PGESTRING saveLockerMsg = "";
    bool    showEverything = false;
    unsigned int    stars = 0;
    unsigned long   inventoryLimit = 0;
    PGESTRING authors = "";
    PGESTRING authors_music = "";
    PGESTRING custom_params;
    all the extended musicbox/tile/path/scene/level fields
    */

    ImageLoader::Run();

    //move player to starting tile
    for (int i = 0; i < numLevel; i++) {
        auto level = SMBXLevel::get(i);
        if (level->isGameStartPoint) {
            auto player = SMBXOverworld::get();
            player->currentPowerup = 1;
            player->momentum.x = level->momentum.x;
            player->momentum.y = level->momentum.y;
            player->currentLevelTitle = level->levelTitle;
            setPathsToVisible(&(level->momentum));
        }

    }
}
