// PlayerInput.h
#ifndef PlayerInput_hhh
#define PlayerInput_hhh

#include <string>
#include <vector>

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
        int up[2] = {0, 38}; //VK_UP
        int down[2] = {0, 40}; //VK_DOWN
        int left[2] = {0, 37}; //VK_LEFT
        int right[2] = {0, 39}; //VK_RIGHT
        int jump[2] = {0, 88}; //VK_X (VK_Z is the default)
        int run[2] = {0, 90}; //VK_Z (VK_X is the default)
        int dropitem[2] = {0, 16}; //VK_SHIFT
        int pause[2] = {0, 27}; //VK_ESCAPE
        int altjump[2] = {0, 65}; //VK_A
        int altrun[2] = {0, 83}; //VK_S
        int special[2] = {0, 68}; //VK_D

        bool upPressing = false;
        bool downPressing = false;
        bool leftPressing = false;
        bool rightPressing = false;
        bool jumpPressing = false;
        bool runPressing = false;
        bool dropitemPressing = false;
        bool pausePressing = false;
        bool altjumpPressing = false;
        bool altrunPressing = false;
        bool specialPressing = false;
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
        // Lua, or the launcher will fill the list up instead
        int up[2] = {0, 0};
        int down[2] = {0, 0};
        int left[2] = {0, 0};
        int right[2] = {0, 0};
        int jump[2] = {0, 0};
        int run[2] = {0, 0};
        int dropitem[2] = {0, 0};
        int pause[2] = {0, 0};
        int altjump[2] = {0, 0};
        int altrun[2] = {0, 0};
        int special[2] = {0, 0};

        bool upPressing = false;
        bool downPressing = false;
        bool leftPressing = false;
        bool rightPressing = false;
        bool jumpPressing = false;
        bool runPressing = false;
        bool dropitemPressing = false;
        bool pausePressing = false;
        bool altjumpPressing = false;
        bool altrunPressing = false;
        bool specialPressing = false;
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
};

#endif
