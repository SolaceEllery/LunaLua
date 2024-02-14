// Child for autocode.cpp
#include "../Autocode.h"
#include "../AutocodeCounter.h"
#include "../../Globals.h"

void Autocode::LunaControl(LunaControlAct act, int val) {
    switch(act)
    {
        case LCA_DemoCounter:
        {
            if(gEpisodeSettings.enableLunaDLLDeathsCounter && gIsLevel)
            {
                gDeathCounter.Init();
                gDeathCounter.Recount();
            }
            break;
        }

        case LCA_SMBXHUD:
        {
            if(val == 1)
                gSMBXHUDSettings.skip = true;
            else
                gSMBXHUDSettings.skip = false;
            break;
        }
        
        case LCA_Invalid:
        default:
            return;
    }
}