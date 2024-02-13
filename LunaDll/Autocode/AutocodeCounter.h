#ifndef DEATHCOUNTER_H
#define DEATHCOUNTER_H

#include <list>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <IniProcessor/ini_processing.h>
#include "../Globals.h"

struct DeathCounter
{
    DeathCounter();
    ~DeathCounter();

    bool Enabled = false;

    void Init();
    void Save();
    void Draw();
    void Quit();

    int CheckLiving();
    void SaveLevelRecord(std::wstring levelFilename, IniProcessing currentIniFile);
    void UpdateDeaths(bool isSaved);
    void Recount();

    int CurrentDeaths = 0;
    int CurrentFails = 0;
    std::wstring DemoTitle = gEpisodeSettings.demosCounterTitle;
};

extern DeathCounter gDeathCounter;

#endif
