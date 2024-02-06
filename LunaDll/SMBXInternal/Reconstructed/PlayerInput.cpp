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
NewSMBXInput g_playerInputPressing[199];

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

void PlayerInput::SetControllerControls(int type, int playerIdx, int controllerButton)
{
    if(type == 1)
    {
        g_playerControllerInputs[playerIdx].up = controllerButton;
    }
    else if(type == 2)
    {
        g_playerControllerInputs[playerIdx].down = controllerButton;
    }
    else if(type == 3)
    {
        g_playerControllerInputs[playerIdx].left = controllerButton;
    }
    else if(type == 4)
    {
        g_playerControllerInputs[playerIdx].right = controllerButton;
    }
    else if(type == 5)
    {
        g_playerControllerInputs[playerIdx].jump = controllerButton;
    }
    else if(type == 6)
    {
        g_playerControllerInputs[playerIdx].run = controllerButton;
    }
    else if(type == 7)
    {
        g_playerControllerInputs[playerIdx].dropitem = controllerButton;
    }
    else if(type == 8)
    {
        g_playerControllerInputs[playerIdx].pause = controllerButton;
    }
    else if(type == 9)
    {
        g_playerControllerInputs[playerIdx].altrun = controllerButton;
    }
    else if(type == 10)
    {
        g_playerControllerInputs[playerIdx].altjump = controllerButton;
    }
    else if(type == 11)
    {
        g_playerControllerInputs[playerIdx].special = controllerButton;
    }
    else if(type == 12)
    {
        g_playerControllerInputs[playerIdx].leftTrigger = controllerButton;
    }
    else if(type == 13)
    {
        g_playerControllerInputs[playerIdx].rightTrigger = controllerButton;
    }
    else
    {
        //Do nothing
    }
}

void PlayerInput::SetControllerIdx(int playerIdx, int controllerIdx)
{
    g_playerControllerInputs[playerIdx].controllerID = controllerIdx;
}

void PlayerInput::SetKeyboardControls(int type, int playerIdx, int virtKey)
{
    if(type == 1)
    {
        g_playerKeyboardInputs[playerIdx].up = virtKey;
    }
    else if(type == 2)
    {
        g_playerKeyboardInputs[playerIdx].down = virtKey;
    }
    else if(type == 3)
    {
        g_playerKeyboardInputs[playerIdx].left = virtKey;
    }
    else if(type == 4)
    {
        g_playerKeyboardInputs[playerIdx].right = virtKey;
    }
    else if(type == 5)
    {
        g_playerKeyboardInputs[playerIdx].jump = virtKey;
    }
    else if(type == 6)
    {
        g_playerKeyboardInputs[playerIdx].run = virtKey;
    }
    else if(type == 7)
    {
        g_playerKeyboardInputs[playerIdx].dropitem = virtKey;
    }
    else if(type == 8)
    {
        g_playerKeyboardInputs[playerIdx].pause = virtKey;
    }
    else if(type == 9)
    {
        g_playerKeyboardInputs[playerIdx].altrun = virtKey;
    }
    else if(type == 10)
    {
        g_playerKeyboardInputs[playerIdx].altjump = virtKey;
    }
    else if(type == 11)
    {
        g_playerKeyboardInputs[playerIdx].special = virtKey;
    }
    else if(type == 12)
    {
        g_playerKeyboardInputs[playerIdx].leftTrigger = virtKey;
    }
    else if(type == 13)
    {
        g_playerKeyboardInputs[playerIdx].rightTrigger = virtKey;
    }
    else
    {
        //Do nothing
    }
}

void PlayerInput::SetKeyboardIdx(int playerIdx, int keyboardIdx)
{
    g_playerKeyboardInputs[playerIdx].keyboardIdx = keyboardIdx;
}

bool PlayerInput::IsPressing(int type, int playerIdx)
{
    PlayerMOB* p = Player::Get(playerIdx);
    int playerIdxC = playerIdx - 1;
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
        return g_playerInputPressing[playerIdxC].specialPressing;
    }
    else if(type == 12)
    {
        return g_playerInputPressing[playerIdxC].leftTriggerPressing;
    }
    else if(type == 13)
    {
        return g_playerInputPressing[playerIdxC].rightTriggerPressing;
    }
    else
    {
        return false;
    }
}

void PlayerInput::SetPressing(int type, int playerIdx, bool value)
{
    PlayerMOB* p = Player::Get(playerIdx);
    int playerIdxC = playerIdx - 1;
    PlayerInput playerInputFunc;

    if(type == 1)
    {
        p->keymap.upKeyState = COMBOOL(value);
    }
    else if(type == 2)
    {
        p->keymap.downKeyState = COMBOOL(value);
    }
    else if(type == 3)
    {
        p->keymap.leftKeyState = COMBOOL(value);
    }
    else if(type == 4)
    {
        p->keymap.rightKeyState = COMBOOL(value);
    }
    else if(type == 5)
    {
        p->keymap.jumpKeyState = COMBOOL(value);
    }
    else if(type == 6)
    {
        p->keymap.runKeyState = COMBOOL(value);
    }
    else if(type == 7)
    {
        p->keymap.dropItemKeyState = COMBOOL(value);
    }
    else if(type == 8)
    {
        p->keymap.pauseKeyState = COMBOOL(value);
    }
    else if(type == 9)
    {
        p->keymap.altRunKeyState = COMBOOL(value);
    }
    else if(type == 10)
    {
        p->keymap.altJumpKeyState = COMBOOL(value);
    }
    else if(type == 11)
    {
        g_playerInputPressing[playerIdxC].specialPressing = value;
    }
    else if(type == 12)
    {
        g_playerInputPressing[playerIdxC].leftTriggerPressing = value;
    }
    else if(type == 13)
    {
        g_playerInputPressing[playerIdxC].rightTriggerPressing = value;
    }
    else
    {
        // Do nothing
    }
}

void PlayerInput::GetKeyboardInput(int virtKey, int keyboardIdx)
{
    PlayerInput playerInputFunc;
    if(gPlayerInputOverhaulToggled)
    {
        For(i, 1, GM_PLAYERS_COUNT)
        {
            
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
            PlayerMOB* p = Player::Get(i);
            int playerIdxC = i - 1;
            int keyboardIdx = g_playerKeyboardInputs[playerIdxC].keyboardIdx;
            
            bool upPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].up] & 0x80) != 0;
            bool downPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].down] & 0x80) != 0;
            bool leftPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].left] & 0x80) != 0;
            bool rightPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].right] & 0x80) != 0;
            bool jumpPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].jump] & 0x80) != 0;
            bool altJumpPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].altjump] & 0x80) != 0;
            bool runPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].run] & 0x80) != 0;
            bool altRunPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].altrun] & 0x80) != 0;
            bool dropItemPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].dropitem] & 0x80) != 0;
            bool pausePressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].pause] & 0x80) != 0;
            bool specialPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].special] & 0x80) != 0;
            bool leftTriggerPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].leftTrigger] & 0x80) != 0;
            bool rightTriggerPressing = (gKeyState[keyboardIdx][g_playerKeyboardInputs[playerIdxC].rightTrigger] & 0x80) != 0;

            if(upPressing)
            {
                p->keymap.upKeyState = COMBOOL(true);
            }
            
            if(downPressing)
            {
                p->keymap.downKeyState = COMBOOL(true);
            }
            
            if(leftPressing)
            {
                p->keymap.leftKeyState = COMBOOL(true);
            }
            
            if(rightPressing)
            {
                p->keymap.rightKeyState = COMBOOL(true);
            }
            
            if(jumpPressing)
            {
                p->keymap.jumpKeyState = COMBOOL(true);
            }

            if(altJumpPressing)
            {
                p->keymap.altJumpKeyState = COMBOOL(true);
            }

            if(runPressing)
            {
                p->keymap.runKeyState = COMBOOL(true);
            }

            if(altRunPressing)
            {
                p->keymap.altRunKeyState = COMBOOL(true);
            }

            if(dropItemPressing)
            {
                p->keymap.dropItemKeyState = COMBOOL(true);
            }

            if(pausePressing)
            {
                p->keymap.pauseKeyState = COMBOOL(true);
            }

            if(specialPressing)
            {
                g_playerInputPressing[playerIdxC].specialPressing = true;
            }
            
            if(leftTriggerPressing)
            {
                g_playerInputPressing[playerIdxC].leftTriggerPressing = true;
            }
            
            if(rightTriggerPressing)
            {
                g_playerInputPressing[playerIdxC].rightTriggerPressing = true;
            }




            if(!upPressing)
            {
                p->keymap.upKeyState = COMBOOL(false);
            }
            
            if(!downPressing)
            {
                p->keymap.downKeyState = COMBOOL(false);
            }
            
            if(!leftPressing)
            {
                p->keymap.leftKeyState = COMBOOL(false);
            }
            
            if(!rightPressing)
            {
                p->keymap.rightKeyState = COMBOOL(false);
            }
            
            if(!jumpPressing)
            {
                p->keymap.jumpKeyState = COMBOOL(false);
            }

            if(!altJumpPressing)
            {
                p->keymap.altJumpKeyState = COMBOOL(false);
            }

            if(!runPressing)
            {
                p->keymap.runKeyState = COMBOOL(false);
            }

            if(!altRunPressing)
            {
                p->keymap.altRunKeyState = COMBOOL(false);
            }

            if(!dropItemPressing)
            {
                p->keymap.dropItemKeyState = COMBOOL(false);
            }

            if(!pausePressing)
            {
                p->keymap.pauseKeyState = COMBOOL(false);
            }

            if(!specialPressing)
            {
                g_playerInputPressing[playerIdxC].specialPressing = false;
            }
            
            if(!leftTriggerPressing)
            {
                g_playerInputPressing[playerIdxC].leftTriggerPressing = false;
            }
            
            if(!rightTriggerPressing)
            {
                g_playerInputPressing[playerIdxC].rightTriggerPressing = false;
            }
        }
    }
}

void PlayerInput::ResetAllInputs()
{
    For(i, 0, 199)
    {
        g_playerKeyboardInputs[i].Reset();
        g_playerControllerInputs[i].Reset();
        g_playerInputPressing[i].Reset();
    }
}
