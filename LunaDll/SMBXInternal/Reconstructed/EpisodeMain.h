// EpisodeLoader.h
#ifndef EpisodeLoader_hhh
#define EpisodeLoader_hhh

#include <string>
#include <vector>

#include "../Menu.h"

class EpisodeMain {
    public:
        EpisodeMain();
        ~EpisodeMain();

        void LaunchEpisode(std::wstring wldPath, int saveSlot, int playerCount, Characters firstCharacter, Characters secondCharacter, bool suppressSound);
        void LoadLevel(std::string levelName, int warpIdx, std::string episodeName, int overworldLvlID, bool suppressSound);

        bool canExecuteViaLua;
        int currentOverworldLvl;
};

#endif
