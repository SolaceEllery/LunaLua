// EpisodeLoader.h
#ifndef EpisodeLoader_hhh
#define EpisodeLoader_hhh

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Menu.h"

class EpisodeMain {
    public:
        EpisodeMain();
        ~EpisodeMain();

        // loading functions
        void preLoadMainMenu();
        void loadMainMenu(std::string mainMenuLvl);

        void LaunchEpisode(std::wstring wldPath, int saveSlot, int playerCount, Characters firstCharacter, Characters secondCharacter, bool suppressSound);
        void LoadLevel(std::string levelName, int warpIdx, std::string episodeName, int overworldLvlID, bool suppressSound);

        bool canExecuteViaLua;
        int currentOverworldLvl;
        
        // loop functions
        void mainMenuLoop();

        // npc config functions
        int getNPCConfigValue(short* configPtr, int npcID);
};

#endif
