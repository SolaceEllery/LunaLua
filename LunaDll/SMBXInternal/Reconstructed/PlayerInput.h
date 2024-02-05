// PlayerInput.h
#ifndef PlayerInput_hhh
#define PlayerInput_hhh

#include <string>
#include <vector>
#include <windows.h>

#define GM_MAX_PLAYER_INPUTS = 11

extern bool gPlayerInputOverhaulToggled;

struct NewSMBXInputKeyboard
{
    int up[2];
    int down[2];
    int left[2];
    int right[2];
    int jump[2];
    int run[2];
    int dropitem[2];
    int pause[2];
    int altjump[2];
    int altrun[2];
    int special[2];
    
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

    // Constructor
    NewSMBXInputKeyboard()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        up[0] = 1;
        down[0] = 1;
        left[0] = 1;
        right[0] = 1;
        jump[0] = 1;
        run[0] = 1;
        dropitem[0] = 1;
        pause[0] = 1;
        altjump[0] = 1;
        altrun[0] = 1;
        special[0] = 1;

        up[1] = VK_UP;
        down[1] = VK_DOWN;
        left[1] = VK_LEFT;
        right[1] = VK_RIGHT;
        jump[1] = 0x58; //VK_Z is the default
        run[1] = 0x5A; //VK_X is the default
        dropitem[1] = VK_SHIFT;
        pause[1] = VK_ESCAPE;
        altjump[1] = 0x41;
        altrun[1] = 0x53;
        special[1] = 0x44;

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
    }
};

struct NewSMBXInputController
{
    int up[2];
    int down[2];
    int left[2];
    int right[2];
    int jump[2];
    int run[2];
    int dropitem[2];
    int pause[2];
    int altjump[2];
    int altrun[2];
    int special[2];

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

    // Constructor
    NewSMBXInputController()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        // Lua, or the launcher, will fill the list up instead
        up[0] = 1;
        down[0] = 1;
        left[0] = 1;
        right[0] = 1;
        jump[0] = 1;
        run[0] = 1;
        dropitem[0] = 1;
        pause[0] = 1;
        altjump[0] = 1;
        altrun[0] = 1;
        special[0] = 1;

        up[1] = 0;
        down[1] = 0;
        left[1] = 0;
        right[1] = 0;
        jump[1] = 0;
        run[1] = 0;
        dropitem[1] = 0;
        pause[1] = 0;
        altjump[1] = 0;
        altrun[1] = 0;
        special[1] = 0;

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
    }
};

//0 = 1, 199 = 200
extern NewSMBXInputKeyboard g_playerKeyboardInputs[199];
extern NewSMBXInputController g_playerControllerInputs[199];

class PlayerInput {
    public:
        PlayerInput();
        ~PlayerInput();

        void SetControllerControls(int type, int playerIdx, int controllerButton, int controllerID);
        void SetKeyboardControls(int type, int playerIdx, int virtKey, int keyboardIdx);

        void GetKeyboardInput(int virtKey, int keyboardIdx);
        
        void SetKeyboardIdx(int playerIdx, int keyboardIdx);
        void SetControllerIdx(int playerIdx, int controllerIdx);

        bool IsPressing(int type, int playerIdx);

        bool Toggle(bool enable);
        void Update();
        void ResetAllInputs();
};

#endif
