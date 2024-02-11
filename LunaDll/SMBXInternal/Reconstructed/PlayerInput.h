// PlayerInput.h
#ifndef PlayerInput_hhh
#define PlayerInput_hhh

#include <string>
#include <vector>
#include <windows.h>

#include "../../DefinesKeyboard.h"

#define GM_MAX_PLAYER_INPUTS = 11

extern bool gPlayerInputOverhaulToggled;

struct NewSMBXInput
{
    bool upPressing;
    bool downPressing;
    bool leftPressing;
    bool rightPressing;
    bool jumpPressing;
    bool runPressing;
    bool dropitemPressing;
    bool pausePressing;
    bool altjumpPressing;
    bool altrunPressing;
    bool specialPressing;
    bool leftTriggerPressing;
    bool rightTriggerPressing;

    int currentInputType;

    // Constructor
    NewSMBXInput()
    {
        Reset();
    }
    
    void Reset()
    {
        upPressing = false;
        downPressing = false;
        leftPressing = false;
        rightPressing = false;
        jumpPressing = false;
        runPressing = false;
        dropitemPressing = false;
        pausePressing = false;
        altjumpPressing = false;
        altrunPressing = false;
        specialPressing = false;
        leftTriggerPressing = false;
        rightTriggerPressing = false;

        currentInputType = 0;
    }
};

struct NewSMBXInputKeyboard
{
    int up;
    int down;
    int left;
    int right;
    int jump;
    int run;
    int dropitem;
    int pause;
    int altjump;
    int altrun;
    int special;
    int leftTrigger;
    int rightTrigger;
    
    

    int keyboardIdx;

    // Constructor
    NewSMBXInputKeyboard()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        up = VK_UP;
        down = VK_DOWN;
        left = VK_LEFT;
        right = VK_RIGHT;
        jump = VK_X; // VK_Z is the default config for 1.3, I switched them for now
        run = VK_Z; // VK_X is the default config for 1.3, I switched them for now
        dropitem = VK_SHIFT;
        pause = VK_ESCAPE;
        altjump = VK_A;
        altrun = VK_S;
        special = VK_D;
        leftTrigger = VK_Q;
        rightTrigger = VK_W;

        keyboardIdx = 0;
    }
};

struct NewSMBXInputController
{
    int up;
    int down;
    int left;
    int right;
    int jump;
    int run;
    int dropitem;
    int pause;
    int altjump;
    int altrun;
    int special;
    int leftTrigger;
    int rightTrigger;
    
    int controllerID;

    // Constructor
    NewSMBXInputController()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        controllerID = 0;

        up = 0;
        down = 1;
        left = 2;
        right = 3;

        jump = 1;
        run = 2;
        dropitem = 10;
        pause = 7;
        altjump = 11;
        altrun = 3;
        special = 0;
        leftTrigger = 4;
        rightTrigger = 5;
    }
};

//0 = 1, 199 = 200
extern NewSMBXInputKeyboard g_playerKeyboardInputs[199];
extern NewSMBXInputController g_playerControllerInputs[199];
extern NewSMBXInput g_playerInputPressing[199];

class PlayerInput {
    public:
        PlayerInput();
        ~PlayerInput();

        void SetControllerControls(int type, int playerIdx, int controllerButton, bool isPermanent);
        void SetKeyboardControls(int type, int playerIdx, int virtKey, bool isPermanent);
        
        void SetKeyboardIdx(int playerIdx, int keyboardIdx, bool isPermanent);
        void SetControllerIdx(int playerIdx, int controllerIdx, bool isPermanent);

        void SetPressing(int type, int playerIdx, bool value);
        bool IsPressing(int type, int playerIdx);

        bool Toggle(bool enable);
        void Update();

        void RefreshAllInputs(bool isWritten, bool isRead);
        void ResetAllInputs();
};

#endif
