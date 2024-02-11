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
        return true;
    }
    else
    {
        gDisablePlayerKeys = false;
        return false;
    }
}

void PlayerInput::SetControllerControls(int type, int playerIdx, int controllerButton, bool isPermanent)
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

    if(isPermanent)
    {
        gPlayerInput.RefreshAllInputs(true, false);
    }
}

void PlayerInput::SetControllerIdx(int playerIdx, int controllerIdx, bool isPermanent)
{
    g_playerControllerInputs[playerIdx].controllerID = controllerIdx;

    if(isPermanent)
    {
        gPlayerInput.RefreshAllInputs(true, false);
    }
}

void PlayerInput::SetKeyboardControls(int type, int playerIdx, int virtKey, bool isPermanent)
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

    if(isPermanent)
    {
        gPlayerInput.RefreshAllInputs(true, false);
    }
}

void PlayerInput::SetKeyboardIdx(int playerIdx, int keyboardIdx, bool isPermanent)
{
    g_playerKeyboardInputs[playerIdx].keyboardIdx = keyboardIdx;

    if(isPermanent)
    {
        gPlayerInput.RefreshAllInputs(true, false);
    }
}

bool PlayerInput::IsPressing(int type, int playerIdx)
{
    PlayerMOB* p = Player::Get(playerIdx);
    int playerIdxC = playerIdx - 1;

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

void PlayerInput::Update()
{
    if(gPlayerInputOverhaulToggled)
    {
        forsim(i, 1, GM_PLAYERS_COUNT)
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
                g_playerInputPressing[playerIdxC].upPressing = true;
            }
            
            if(downPressing)
            {
                p->keymap.downKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].downPressing = true;
            }
            
            if(leftPressing)
            {
                p->keymap.leftKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].leftPressing = true;
            }
            
            if(rightPressing)
            {
                p->keymap.rightKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].rightPressing = true;
            }
            
            if(jumpPressing)
            {
                p->keymap.jumpKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].jumpPressing = true;
            }

            if(altJumpPressing)
            {
                p->keymap.altJumpKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].altjumpPressing = true;
            }

            if(runPressing)
            {
                p->keymap.runKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].runPressing = true;
            }

            if(altRunPressing)
            {
                p->keymap.altRunKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].altrunPressing = true;
            }

            if(dropItemPressing)
            {
                p->keymap.dropItemKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].dropitemPressing = true;
            }

            if(pausePressing)
            {
                p->keymap.pauseKeyState = COMBOOL(true);
                g_playerInputPressing[playerIdxC].pausePressing = true;
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
                g_playerInputPressing[playerIdxC].upPressing = false;
            }
            
            if(!downPressing)
            {
                p->keymap.downKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].downPressing = false;
            }
            
            if(!leftPressing)
            {
                p->keymap.leftKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].leftPressing = false;
            }
            
            if(!rightPressing)
            {
                p->keymap.rightKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].rightPressing = false;
            }
            
            if(!jumpPressing)
            {
                p->keymap.jumpKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].jumpPressing = false;
            }

            if(!altJumpPressing)
            {
                p->keymap.altJumpKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].altjumpPressing = false;
            }

            if(!runPressing)
            {
                p->keymap.runKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].runPressing = false;
            }

            if(!altRunPressing)
            {
                p->keymap.altRunKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].altrunPressing = false;
            }

            if(!dropItemPressing)
            {
                p->keymap.dropItemKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].dropitemPressing = false;
            }

            if(!pausePressing)
            {
                p->keymap.pauseKeyState = COMBOOL(false);
                g_playerInputPressing[playerIdxC].pausePressing = false;
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

void PlayerInput::RefreshAllInputs(bool isWritten, bool isRead)
{
    if(isWritten && isRead)
    {
        // Invalid, just return
        return;
    }
    std::string appDirToIni = gAppPathUTF8 + "\\inputs.ini";
    if(file_existsX(appDirToIni))
    {
        IniProcessing inputConfig(appDirToIni);
        forsim(i, 0, 199)
        {
            inputConfig.beginGroup("Player " + std::to_string(i + 1) + " Controls");
            if(!isRead)
            {
                inputConfig.setValue("keyboard_up", g_playerKeyboardInputs[i].up);
                inputConfig.setValue("keyboard_down", g_playerKeyboardInputs[i].down);
                inputConfig.setValue("keyboard_left", g_playerKeyboardInputs[i].left);
                inputConfig.setValue("keyboard_right", g_playerKeyboardInputs[i].right);
                inputConfig.setValue("keyboard_jump", g_playerKeyboardInputs[i].jump);
                inputConfig.setValue("keyboard_run", g_playerKeyboardInputs[i].run);
                inputConfig.setValue("keyboard_dropitem", g_playerKeyboardInputs[i].dropitem);
                inputConfig.setValue("keyboard_pause", g_playerKeyboardInputs[i].pause);
                inputConfig.setValue("keyboard_altjump", g_playerKeyboardInputs[i].altjump);
                inputConfig.setValue("keyboard_altrun", g_playerKeyboardInputs[i].altrun);
                inputConfig.setValue("keyboard_special", g_playerKeyboardInputs[i].special);
                inputConfig.setValue("keyboard_leftTrigger", g_playerKeyboardInputs[i].leftTrigger);
                inputConfig.setValue("keyboard_rightTrigger", g_playerKeyboardInputs[i].rightTrigger);

                inputConfig.setValue("keyboard_inputType", g_playerKeyboardInputs[i].keyboardIdx);

                inputConfig.setValue("controller_up", g_playerControllerInputs[i].up);
                inputConfig.setValue("controller_down", g_playerControllerInputs[i].down);
                inputConfig.setValue("controller_left", g_playerControllerInputs[i].left);
                inputConfig.setValue("controller_right", g_playerControllerInputs[i].right);
                inputConfig.setValue("controller_jump", g_playerControllerInputs[i].jump);
                inputConfig.setValue("controller_run", g_playerControllerInputs[i].run);
                inputConfig.setValue("controller_dropitem", g_playerControllerInputs[i].dropitem);
                inputConfig.setValue("controller_pause", g_playerControllerInputs[i].pause);
                inputConfig.setValue("controller_altjump", g_playerControllerInputs[i].altjump);
                inputConfig.setValue("controller_altrun", g_playerControllerInputs[i].altrun);
                inputConfig.setValue("controller_special", g_playerControllerInputs[i].special);
                inputConfig.setValue("controller_leftTrigger", g_playerControllerInputs[i].leftTrigger);
                inputConfig.setValue("controller_rightTrigger", g_playerControllerInputs[i].rightTrigger);
                
                inputConfig.setValue("controller_inputType", g_playerControllerInputs[i].controllerID);
            }
            else
            {
                g_playerKeyboardInputs[i].up = inputConfig.value("keyboard_up", VK_UP).toInt();
                g_playerKeyboardInputs[i].down = inputConfig.value("keyboard_down", VK_DOWN).toInt();
                g_playerKeyboardInputs[i].left = inputConfig.value("keyboard_left", VK_LEFT).toInt();
                g_playerKeyboardInputs[i].right = inputConfig.value("keyboard_right", VK_RIGHT).toInt();
                g_playerKeyboardInputs[i].jump = inputConfig.value("keyboard_jump", VK_X).toInt();
                g_playerKeyboardInputs[i].run = inputConfig.value("keyboard_run", VK_Z).toInt();
                g_playerKeyboardInputs[i].dropitem = inputConfig.value("keyboard_dropitem", VK_SHIFT).toInt();
                g_playerKeyboardInputs[i].pause = inputConfig.value("keyboard_pause", VK_ESCAPE).toInt();
                g_playerKeyboardInputs[i].altjump = inputConfig.value("keyboard_altjump", VK_A).toInt();
                g_playerKeyboardInputs[i].altrun = inputConfig.value("keyboard_altrun", VK_S).toInt();
                g_playerKeyboardInputs[i].special = inputConfig.value("keyboard_special", VK_D).toInt();
                g_playerKeyboardInputs[i].leftTrigger = inputConfig.value("keyboard_leftTrigger", VK_Q).toInt();
                g_playerKeyboardInputs[i].rightTrigger = inputConfig.value("keyboard_rightTrigger", VK_W).toInt();

                g_playerKeyboardInputs[i].keyboardIdx = inputConfig.value("keyboard_inputType", 0).toInt();

                g_playerControllerInputs[i].up = inputConfig.value("controller_up", 0).toInt();
                g_playerControllerInputs[i].down = inputConfig.value("controller_down", 1).toInt();
                g_playerControllerInputs[i].left = inputConfig.value("controller_left", 2).toInt();
                g_playerControllerInputs[i].right = inputConfig.value("controller_right", 3).toInt();
                g_playerControllerInputs[i].jump = inputConfig.value("controller_jump", 1).toInt();
                g_playerControllerInputs[i].run = inputConfig.value("controller_run", 2).toInt();
                g_playerControllerInputs[i].dropitem = inputConfig.value("controller_dropitem", 10).toInt();
                g_playerControllerInputs[i].pause = inputConfig.value("controller_pause", 7).toInt();
                g_playerControllerInputs[i].altjump = inputConfig.value("controller_altjump", 11).toInt();
                g_playerControllerInputs[i].altrun = inputConfig.value("controller_altrun", 3).toInt();
                g_playerControllerInputs[i].special = inputConfig.value("controller_special", 0).toInt();
                g_playerControllerInputs[i].leftTrigger = inputConfig.value("controller_leftTrigger", 4).toInt();
                g_playerControllerInputs[i].rightTrigger = inputConfig.value("controller_rightTrigger", 5).toInt();

                g_playerControllerInputs[i].controllerID = inputConfig.value("controller_inputType", 0).toInt();
            }
            inputConfig.endGroup();
        }
        if(!isRead)
        {
            inputConfig.writeIniFile();
        }
        inputConfig.close();
    }
}

void PlayerInput::ResetAllInputs()
{
    std::string appDirToIni = gAppPathUTF8 + "\\inputs.ini";
    if(!file_existsX(appDirToIni))
    {
        std::wstring appDirToIniWS = Str2WStr(appDirToIni);
        IniProcessing inputConfig(appDirToIni);
        forsim(i, 0, 199)
        {
            g_playerKeyboardInputs[i].Reset();
            g_playerControllerInputs[i].Reset();
            g_playerInputPressing[i].Reset();

            inputConfig.beginGroup("Player " + std::to_string(i + 1) + " Controls");
 
            inputConfig.setValue("keyboard_up", g_playerKeyboardInputs[i].up);
            inputConfig.setValue("keyboard_down", g_playerKeyboardInputs[i].down);
            inputConfig.setValue("keyboard_left", g_playerKeyboardInputs[i].left);
            inputConfig.setValue("keyboard_right", g_playerKeyboardInputs[i].right);
            inputConfig.setValue("keyboard_jump", g_playerKeyboardInputs[i].jump);
            inputConfig.setValue("keyboard_run", g_playerKeyboardInputs[i].run);
            inputConfig.setValue("keyboard_dropitem", g_playerKeyboardInputs[i].dropitem);
            inputConfig.setValue("keyboard_pause", g_playerKeyboardInputs[i].pause);
            inputConfig.setValue("keyboard_altjump", g_playerKeyboardInputs[i].altjump);
            inputConfig.setValue("keyboard_altrun", g_playerKeyboardInputs[i].altrun);
            inputConfig.setValue("keyboard_special", g_playerKeyboardInputs[i].special);
            inputConfig.setValue("keyboard_leftTrigger", g_playerKeyboardInputs[i].leftTrigger);
            inputConfig.setValue("keyboard_rightTrigger", g_playerKeyboardInputs[i].rightTrigger);

            inputConfig.setValue("keyboard_inputType", g_playerKeyboardInputs[i].keyboardIdx);

            inputConfig.setValue("controller_up", g_playerControllerInputs[i].up);
            inputConfig.setValue("controller_down", g_playerControllerInputs[i].down);
            inputConfig.setValue("controller_left", g_playerControllerInputs[i].left);
            inputConfig.setValue("controller_right", g_playerControllerInputs[i].right);
            inputConfig.setValue("controller_jump", g_playerControllerInputs[i].jump);
            inputConfig.setValue("controller_run", g_playerControllerInputs[i].run);
            inputConfig.setValue("controller_dropitem", g_playerControllerInputs[i].dropitem);
            inputConfig.setValue("controller_pause", g_playerControllerInputs[i].pause);
            inputConfig.setValue("controller_altjump", g_playerControllerInputs[i].altjump);
            inputConfig.setValue("controller_altrun", g_playerControllerInputs[i].altrun);
            inputConfig.setValue("controller_special", g_playerControllerInputs[i].special);
            inputConfig.setValue("controller_leftTrigger", g_playerControllerInputs[i].leftTrigger);
            inputConfig.setValue("controller_rightTrigger", g_playerControllerInputs[i].rightTrigger);
            
            inputConfig.setValue("controller_inputType", g_playerControllerInputs[i].controllerID);

            inputConfig.endGroup();
        }
        inputConfig.writeIniFile();
        inputConfig.close();
    }
}
