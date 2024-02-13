#include "AutocodeCounter.h"
#include "../Globals.h"
#include "../Misc/MiscFuncs.h"
#include "../GlobalFuncs.h"
#include "../Defines.h"
#include "../SMBXInternal/PlayerMOB.h"
#include "../SMBXInternal/Functions.h"
#include "../SMBXInternal/Types.h"
#include "../Misc/VB6StrPtr.h"
#include "../Misc/VB6Bool.h"
#include "../Rendering/Rendering.h"
#include "../Misc/RuntimeHook.h"
#include "../Rendering/RenderOps/RenderStringOp.h"
#include "../Rendering/GL/GLContextManager.h"
#include <IniProcessor/ini_processing.h>

DeathCounter gDeathCounter;

// CTOR
DeathCounter::DeathCounter()
{
    if(gEpisodeSettings.enableLunaDLLDeathsCounter)
    {
        gDeathCounter.Enabled = true;
    }
    else
    {
        gDeathCounter.Enabled = false;
    }
}

DeathCounter::~DeathCounter()
{
    gDeathCounter.Enabled = false;
}

void DeathCounter::Init()
{
    bool noLunaDLLFile = false;
    std::string episodeDirToIni = WStr2Str(gEpisodeSettings.episodeDirectory) + "\\LunaDLL.ini";
    IniProcessing lunaDLLConfig(episodeDirToIni);
    // If there's no death counter information, create a file with default values in it
    if(!lunaDLLConfig.beginGroup("demos-counter"))
    {
        noLunaDLLFile = true;
        lunaDLLConfig.setValue("deaths", 0);
        lunaDLLConfig.setValue("fails", 0);
    }
    else // else just read the values from the file
    {
        gDeathCounter.CurrentDeaths = lunaDLLConfig.value("deaths", 0).toInt();
        gDeathCounter.CurrentFails = lunaDLLConfig.value("fails", 0).toInt();
    }
    lunaDLLConfig.endGroup();
    if(noLunaDLLFile)
    {
        lunaDLLConfig.writeIniFile();
    }
    lunaDLLConfig.close();
}

void DeathCounter::SaveLevelRecord(std::wstring levelFilename, IniProcessing currentIniFile)
{
    std::string episodeDirToIni = WStr2Str(gEpisodeSettings.episodeDirectory) + "\\LunaDLL.ini";
    IniProcessing lunaDLLConfig(episodeDirToIni);
    // Get the fails group
    lunaDLLConfig.beginGroup("fails-" + WStr2Str(levelFilename));
    // Get the count
    int levelFails = lunaDLLConfig.value("levelFails", 0).toInt();
    // Increase a fail
    levelFails = levelFails + 1;
    // Set the value
    lunaDLLConfig.setValue("levelFails", levelFails);
    // Increase the global fails variable
    gDeathCounter.CurrentFails = gDeathCounter.CurrentFails + 1;
    // End the group
    lunaDLLConfig.endGroup();
}

void DeathCounter::Save()
{
    std::string episodeDirToIni = WStr2Str(gEpisodeSettings.episodeDirectory) + "\\LunaDLL.ini";
    IniProcessing lunaDLLConfig(episodeDirToIni);
    // Save the total demo counter
    if(lunaDLLConfig.beginGroup("demos-counter"))
    {
        lunaDLLConfig.setValue("deaths", gDeathCounter.CurrentDeaths);
        lunaDLLConfig.setValue("fails", gDeathCounter.CurrentFails);
    }
    lunaDLLConfig.endGroup();

    // now save the current level's fails
    gDeathCounter.SaveLevelRecord((std::wstring)GM_LVLFILENAME_PTR, lunaDLLConfig);

    // now write the ini file and close
    lunaDLLConfig.writeIniFile();
    lunaDLLConfig.close();
}

int DeathCounter::CheckLiving()
{
    for(int i = 1; i <= GM_PLAYERS_COUNT; i++)
    {
        PlayerMOB* demo = Player::Get(i);
        if(demo->DeathTimer == 0 && demo->DeathState == 0)
        {
            return 1;
        }
    }
    return 0;
}

void DeathCounter::UpdateDeaths(bool isSaved)
{
    for(int i = 1; i <= GM_PLAYERS_COUNT; i++)
    {
        PlayerMOB* demo = Player::Get(i);
        if(gDeathCounter.CheckLiving() == 0)
        {
            if(demo->DeathTimer == 50)
            {
                gDeathCounter.CurrentDeaths++;

                if(isSaved)
                {
                    DeathCounter::Save();
                }
            }
        }
    }
}

void DeathCounter::Recount()
{
    if(!gDeathCounter.Enabled && !gIsLevel)
    {
        return;
    }

    int total = 0;
    gDeathCounter.CurrentFails = 0;

    // Open the ini file
    std::string episodeDirToIni = WStr2Str(gEpisodeSettings.episodeDirectory) + "\\LunaDLL.ini";
    IniProcessing lunaDLLConfig(episodeDirToIni);
    // Get the fails from the current level file
    lunaDLLConfig.beginGroup("fails-" + WStr2Str((std::wstring)GM_LVLFILENAME_PTR));
    int levelFails = lunaDLLConfig.value("levelFails", 0).toInt();
    // Apply it to the current global fail counter
    gDeathCounter.CurrentFails = levelFails;
}

void DeathCounter::Draw()
{
    if(!gDeathCounter.Enabled && !gIsLevel)
    {
        return;
    }

    RenderStringOp* printTextDemosOp = new RenderStringOp(gDeathCounter.DemoTitle, 3, g_GLContextManager.CenterDrawingThings(80, true), g_GLContextManager.CenterDrawingThings(26, false));
    printTextDemosOp->m_renderPriority = 5;
    Renderer::Get().AddOp(printTextDemosOp);

    std::wstring counter = Str2WStr(std::to_string(gDeathCounter.CurrentDeaths) + " / " + std::to_string(gDeathCounter.CurrentFails));
    float minusOffset = (float)(123 - counter.size() * 8);

    RenderStringOp* printTextCounterOp = new RenderStringOp(gDeathCounter.DemoTitle, 3, g_GLContextManager.CenterDrawingThings((int)minusOffset, true), g_GLContextManager.CenterDrawingThings(48, false));
    printTextCounterOp->m_renderPriority = 5;
    Renderer::Get().AddOp(printTextCounterOp);
    
    gDeathCounter.UpdateDeaths(true);
}

void DeathCounter::Quit()
{
    gDeathCounter.Enabled = false;
}
