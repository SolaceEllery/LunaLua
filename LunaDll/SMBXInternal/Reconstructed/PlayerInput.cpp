#include "PlayerInput.h"

#include <string>
#include <vector>
#include <windows.h>

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

void PlayerInput::SetControllerControls(int type, int playerIdx, int controllerButton, int controllerID)
{
    if(type == 1)
    {
        g_playerControllerInputs[playerIdx].up[1] = controllerID;
        g_playerControllerInputs[playerIdx].up[0] = controllerButton;
    }
    else if(type == 2)
    {
        g_playerControllerInputs[playerIdx].down[1] = controllerID;
        g_playerControllerInputs[playerIdx].down[0] = controllerButton;
    }
    else if(type == 3)
    {
        g_playerControllerInputs[playerIdx].left[1] = controllerID;
        g_playerControllerInputs[playerIdx].left[0] = controllerButton;
    }
    else if(type == 4)
    {
        g_playerControllerInputs[playerIdx].right[1] = controllerID;
        g_playerControllerInputs[playerIdx].right[0] = controllerButton;
    }
    else if(type == 5)
    {
        g_playerControllerInputs[playerIdx].jump[1] = controllerID;
        g_playerControllerInputs[playerIdx].jump[0] = controllerButton;
    }
    else if(type == 6)
    {
        g_playerControllerInputs[playerIdx].run[1] = controllerID;
        g_playerControllerInputs[playerIdx].run[0] = controllerButton;
    }
    else if(type == 7)
    {
        g_playerControllerInputs[playerIdx].dropitem[1] = controllerID;
        g_playerControllerInputs[playerIdx].dropitem[0] = controllerButton;
    }
    else if(type == 8)
    {
        g_playerControllerInputs[playerIdx].pause[1] = controllerID;
        g_playerControllerInputs[playerIdx].pause[0] = controllerButton;
    }
    else if(type == 9)
    {
        g_playerControllerInputs[playerIdx].altrun[1] = controllerID;
        g_playerControllerInputs[playerIdx].altrun[0] = controllerButton;
    }
    else if(type == 10)
    {
        g_playerControllerInputs[playerIdx].altjump[1] = controllerID;
        g_playerControllerInputs[playerIdx].altjump[0] = controllerButton;
    }
    else if(type == 11)
    {
        g_playerControllerInputs[playerIdx].special[1] = controllerID;
        g_playerControllerInputs[playerIdx].special[0] = controllerButton;
    }
    else
    {
        //Do nothing
    }
}

void PlayerInput::SetControllerIdx(int playerIdx, int controllerIdx)
{
    g_playerControllerInputs[playerIdx].up[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].down[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].left[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].right[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].jump[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].run[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].dropitem[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].pause[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].altrun[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].altjump[1] = controllerIdx;
    g_playerControllerInputs[playerIdx].special[1] = controllerIdx;
}

void PlayerInput::SetKeyboardControls(int type, int playerIdx, int virtKey, int keyboardIdx)
{
    if(type == 1)
    {
        g_playerKeyboardInputs[playerIdx].up[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].up[0] = virtKey;
    }
    else if(type == 2)
    {
        g_playerKeyboardInputs[playerIdx].down[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].down[0] = virtKey;
    }
    else if(type == 3)
    {
        g_playerKeyboardInputs[playerIdx].left[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].left[0] = virtKey;
    }
    else if(type == 4)
    {
        g_playerKeyboardInputs[playerIdx].right[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].right[0] = virtKey;
    }
    else if(type == 5)
    {
        g_playerKeyboardInputs[playerIdx].jump[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].jump[0] = virtKey;
    }
    else if(type == 6)
    {
        g_playerKeyboardInputs[playerIdx].run[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].run[0] = virtKey;
    }
    else if(type == 7)
    {
        g_playerKeyboardInputs[playerIdx].dropitem[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].dropitem[0] = virtKey;
    }
    else if(type == 8)
    {
        g_playerKeyboardInputs[playerIdx].pause[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].pause[0] = virtKey;
    }
    else if(type == 9)
    {
        g_playerKeyboardInputs[playerIdx].altrun[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].altrun[0] = virtKey;
    }
    else if(type == 10)
    {
        g_playerKeyboardInputs[playerIdx].altjump[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].altjump[0] = virtKey;
    }
    else if(type == 11)
    {
        g_playerKeyboardInputs[playerIdx].special[1] = keyboardIdx;
        g_playerKeyboardInputs[playerIdx].special[0] = virtKey;
    }
    else
    {
        //Do nothing
    }
}

void PlayerInput::SetKeyboardIdx(int playerIdx, int keyboardIdx)
{
    g_playerKeyboardInputs[playerIdx].up[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].down[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].left[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].right[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].jump[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].run[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].dropitem[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].pause[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].altrun[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].altjump[1] = keyboardIdx;
    g_playerKeyboardInputs[playerIdx].special[1] = keyboardIdx;
}

bool PlayerInput::IsPressing(int type, int playerIdx)
{
    PlayerMOB* p = Player::Get(playerIdx);
    PlayerInput playerInputFunc;
    if(type == 1)
    {
        return COMBOOL(p->keymap.upKeyState);
    }
    else if(type == 2)
    {
        return COMBOOL(p->keymap.downKeyState);
    }
    else if(type == 3)
    {
        return COMBOOL(p->keymap.leftKeyState);
    }
    else if(type == 4)
    {
        return COMBOOL(p->keymap.rightKeyState);
    }
    else if(type == 5)
    {
        return COMBOOL(p->keymap.jumpKeyState);
    }
    else if(type == 6)
    {
        return COMBOOL(p->keymap.runKeyState);
    }
    else if(type == 7)
    {
        return COMBOOL(p->keymap.dropItemKeyState);
    }
    else if(type == 8)
    {
        return COMBOOL(p->keymap.pauseKeyState);
    }
    else if(type == 9)
    {
        return COMBOOL(p->keymap.altRunKeyState);
    }
    else if(type == 10)
    {
        return COMBOOL(p->keymap.altJumpKeyState);
    }
    else if(type == 11)
    {
        return playerSpecialKeyPressed[playerIdx];
    }
    else
    {
        return false;
    }
}

void PlayerInput::GetKeyboardInput(int virtKey, int keyboardIdx)
{
    PlayerInput playerInputFunc;
    if(gPlayerInputOverhaulToggled)
    {
        For(i, 1, GM_PLAYERS_COUNT)
        {
            PlayerMOB* p = Player::Get(i);
            if(virtKey == g_playerKeyboardInputs[i].up[1] && keyboardIdx == g_playerKeyboardInputs[i].up[0])
            {
                p->keymap.upKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].up[1]))
            {
                p->keymap.upKeyState = COMBOOL(false);
            }
            
            if(virtKey == g_playerKeyboardInputs[i].down[1] && keyboardIdx == g_playerKeyboardInputs[i].down[0])
            {
                p->keymap.downKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].down[1]))
            {
                p->keymap.downKeyState = COMBOOL(false);
            }
            
            if(virtKey == g_playerKeyboardInputs[i].left[1] && keyboardIdx == g_playerKeyboardInputs[i].left[0])
            {
                p->keymap.leftKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].left[1]))
            {
                p->keymap.leftKeyState = COMBOOL(false);
            }
            
            if(virtKey == g_playerKeyboardInputs[i].right[1] && keyboardIdx == g_playerKeyboardInputs[i].right[0])
            {
                p->keymap.rightKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].right[1]))
            {
                p->keymap.rightKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].jump[1] && keyboardIdx == g_playerKeyboardInputs[i].jump[0])
            {
                p->keymap.jumpKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].jump[1]))
            {
                p->keymap.jumpKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].altjump[1] && keyboardIdx == g_playerKeyboardInputs[i].altjump[0])
            {
                p->keymap.altJumpKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].altjump[1]))
            {
                p->keymap.altJumpKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].run[1] && keyboardIdx == g_playerKeyboardInputs[i].run[0])
            {
                p->keymap.runKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].run[1]))
            {
                p->keymap.runKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].altrun[1] && keyboardIdx == g_playerKeyboardInputs[i].altrun[0])
            {
                p->keymap.altRunKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].altrun[1]))
            {
                p->keymap.altRunKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].dropitem[1] && keyboardIdx == g_playerKeyboardInputs[i].dropitem[0])
            {
                p->keymap.dropItemKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].dropitem[1]))
            {
                p->keymap.dropItemKeyState = COMBOOL(false);
            }

            if(virtKey == g_playerKeyboardInputs[i].pause[1] && keyboardIdx == g_playerKeyboardInputs[i].pause[0])
            {
                p->keymap.pauseKeyState = COMBOOL(true);
            }
            else if(!(virtKey == g_playerKeyboardInputs[i].pause[1]))
            {
                p->keymap.pauseKeyState = COMBOOL(false);
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
}

void PlayerInput::Update()
{
    PlayerInput playerInputFunc;
    if(gPlayerInputOverhaulToggled)
    {
        For(i, 1, GM_PLAYERS_COUNT)
        {
            
        }
    }
}
