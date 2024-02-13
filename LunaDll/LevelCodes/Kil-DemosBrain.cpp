#include "LevelCodes.h"
#include "../SMBXInternal/PlayerMOB.h"
#include "../Globals.h"
#include "../SMBXInternal/Layer.h"

void DemosBrainCode()
{
    if(gEpisodeSettings.enableLunaDLLInternalLevelCodes)
    {
        PlayerMOB* demo = Player::Get(1);
        LayerControl* scroll_layer = Layer::Get(3);

        Layer::SetYSpeed(scroll_layer, (float)(demo->momentum.speedX * -1));
    }
}