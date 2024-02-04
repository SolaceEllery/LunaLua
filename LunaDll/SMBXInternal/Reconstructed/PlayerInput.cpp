#include "PlayerInput.h"

#include <string>
#include <vector>

#include "../../SMBXInternal/PlayerMOB.h"
#include "../../Defines.h"
#include "../../Globals.h"
#include "../../GlobalFuncs.h"

bool gPlayerInputOverhaulToggled = false;
NewSMBXInputKeyboard g_playerKeyboardInputs[199];
NewSMBXInputController g_playerControllerInputs[199];

PlayerInput::PlayerInput()
{}

PlayerInput::~PlayerInput() {}

bool PlayerInput::Toggle(bool enable)
{
    if(enable)
    {
        gDisablePlayerKeys = true;
        gPlayerInputOverhaulToggled = true;
        return true;
    }
    else
    {
        gDisablePlayerKeys = false;
        gPlayerInputOverhaulToggled = false;
        return false;
    }
}

void PlayerInput::GetKeyboardInput(int virtKey, int keyboardIdx)
{
    if(gPlayerInputOverhaulToggled)
    {
        For(i, 1, GM_MAX_PLAYERS)
        {
            PlayerMOB* p = Player::Get(i);
            if(virtKey == g_playerKeyboardInputs[i].up[2] && keyboardIdx == g_playerKeyboardInputs[i].up[1])
            {
                p->keymap.upKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].up[2]))
            {
                p->keymap.upKeyState = false;
            }
            
            if(virtKey == g_playerKeyboardInputs[i].down[2] && keyboardIdx == g_playerKeyboardInputs[i].down[1])
            {
                p->keymap.downKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].down[2]))
            {
                p->keymap.downKeyState = false;
            }
            
            if(virtKey == g_playerKeyboardInputs[i].left[2] && keyboardIdx == g_playerKeyboardInputs[i].left[1])
            {
                p->keymap.leftKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].left[2]))
            {
                p->keymap.leftKeyState = false;
            }
            
            if(virtKey == g_playerKeyboardInputs[i].right[2] && keyboardIdx == g_playerKeyboardInputs[i].right[1])
            {
                p->keymap.rightKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].right[2]))
            {
                p->keymap.rightKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].jump[2] && keyboardIdx == g_playerKeyboardInputs[i].jump[1])
            {
                p->keymap.jumpKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].jump[2]))
            {
                p->keymap.jumpKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].altjump[2] && keyboardIdx == g_playerKeyboardInputs[i].altjump[1])
            {
                p->keymap.altJumpKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].altjump[2]))
            {
                p->keymap.altJumpKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].run[2] && keyboardIdx == g_playerKeyboardInputs[i].run[1])
            {
                p->keymap.runKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].run[2]))
            {
                p->keymap.runKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].altrun[2] && keyboardIdx == g_playerKeyboardInputs[i].altrun[1])
            {
                p->keymap.altRunKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].altrun[2]))
            {
                p->keymap.altRunKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].dropitem[2] && keyboardIdx == g_playerKeyboardInputs[i].dropitem[1])
            {
                p->keymap.dropItemKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].dropitem[2]))
            {
                p->keymap.dropItemKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].pause[2] && keyboardIdx == g_playerKeyboardInputs[i].pause[1])
            {
                p->keymap.pauseKeyState = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].pause[2]))
            {
                p->keymap.pauseKeyState = false;
            }

            if(virtKey == g_playerKeyboardInputs[i].special[2] && keyboardIdx == g_playerKeyboardInputs[i].special[1])
            {
                playerSpecialKeyPressed[i] = true;
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].special[2]))
            {
                playerSpecialKeyPressed[i] = false;
            }
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
