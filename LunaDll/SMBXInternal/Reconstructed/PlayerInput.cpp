#include "PlayerInput.h"

#include "../../SMBXInternal/PlayerMOB.h"
#include "../../Defines.h"
#include "../../Globals.h"
#include "../../GlobalFuncs.h"

bool gPlayerInputOverhaulToggled = false;
//0 = 1, 199 = 200
NewSMBXInputKeyboard* g_playerKeyboardInputs[199];
NewSMBXInputKeyboard* g_playerControllerInputs[199];

PlayerInput::PlayerInput()
{}

PlayerInput::~PlayerInput() {}

void PlayerInput::Toggle(bool enable);
{
    if(enable)
    {
        gDisablePlayerKeys = true;
        gPlayerInputOverhaulToggled = true;
    }
    else
    {
        gDisablePlayerKeys = false;
        gPlayerInputOverhaulToggled = false;
    }
}

int PlayerInput::GetKeyboardInput(uint32_t virtKey, int keyboardIdx);
{
    For(i, 1, GM_MAX_PLAYERS)
    {
        PlayerMOB* p = Player::Get(i);
        if(virtKey == g_playerKeyboardInputs[i].up[1] && keyboardIdx == g_playerKeyboardInputs[i].up[0])
        {
            p->upKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].up[1]))
        {
            p->upKeyState = COMBOOL(false);
        }
        
        if(virtKey == g_playerKeyboardInputs[i].down[1] && keyboardIdx == g_playerKeyboardInputs[i].down[0])
        {
            p->downKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].down[1]))
        {
            p->downKeyState = COMBOOL(false);
        }
        
        if(virtKey == g_playerKeyboardInputs[i].left[1] && keyboardIdx == g_playerKeyboardInputs[i].left[0])
        {
            p->leftKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].left[1]))
        {
            p->leftKeyState = COMBOOL(false);
        }
        
        if(virtKey == g_playerKeyboardInputs[i].right[1] && keyboardIdx == g_playerKeyboardInputs[i].right[0])
        {
            p->rightKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].right[1]))
        {
            p->rightKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].jump[1] && keyboardIdx == g_playerKeyboardInputs[i].jump[0])
        {
            p->jumpKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].jump[1]))
        {
            p->jumpKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].altjump[1] && keyboardIdx == g_playerKeyboardInputs[i].altjump[0])
        {
            p->altJumpKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].altjump[1]))
        {
            p->altJumpKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].run[1] && keyboardIdx == g_playerKeyboardInputs[i].run[0])
        {
            p->runKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].run[1]))
        {
            p->runKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].altrun[1] && keyboardIdx == g_playerKeyboardInputs[i].altrun[0])
        {
            p->altRunKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].altrun[1]))
        {
            p->altRunKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].dropitem[1] && keyboardIdx == g_playerKeyboardInputs[i].dropitem[0])
        {
            p->dropItemKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].dropitem[1]))
        {
            p->dropItemKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].pause[1] && keyboardIdx == g_playerKeyboardInputs[i].pause[0])
        {
            p->pauseKeyState = COMBOOL(true);
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].pause[1]))
        {
            p->pauseKeyState = COMBOOL(false);
        }

        if(virtKey == g_playerKeyboardInputs[i].special[1] && keyboardIdx == g_playerKeyboardInputs[i].special[0])
        {
            playerSpecialKeyPressed[i] = true;
        }
        else if(!(virtKey == g_playerKeyboardInputs[i].special[1]))
        {
            playerSpecialKeyPressed[i] = false;
        }
    }
}

void PlayerInput::Update()
{
    PlayerInput playerInputFunc;
    if(gPlayerInputOverhaulToggled)
    {
        For(i, 1, GM_MAX_PLAYERS)
        {
            
        }
    }
}
