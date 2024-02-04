// PlayerInput.h
#ifndef PlayerInput_hhh
#define PlayerInput_hhh

extern bool gPlayerInputOverhaulToggled;
extern NewSMBXInputKeyboard* g_playerKeyboardInputs[199];
extern NewSMBXInputController* g_playerControllerInputs[199];

struct NewSMBXInputKeyboard
{
    unsigned char* up[1];
    unsigned char* down[1];
    unsigned char* left[1];
    unsigned char* right[1];
    unsigned char* jump[1];
    unsigned char* run[1];
    unsigned char* dropitem[1];
    unsigned char* pause[1];
    unsigned char* altjump[1];
    unsigned char* altrun[1];
    unsigned char* special[1];
    
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
        unsigned char* up[1] = {0, 38}; //VK_UP
        unsigned char* down[1] = {0, 40}; //VK_DOWN
        unsigned char* left[1] = {0, 37}; //VK_LEFT
        unsigned char* right[1] = {0, 39}; //VK_RIGHT
        unsigned char* jump[1] = {0, 90}; //VK_Z
        unsigned char* run[1] = {0, 88}; //VK_X
        unsigned char* dropitem[1] = {0, 16}; //VK_SHIFT
        unsigned char* pause[1] = {0, 27}; //VK_ESCAPE
        unsigned char* altjump[1] = {0, 65}; //VK_A
        unsigned char* altrun[1] = {0, 83}; //VK_S
        unsigned char* special[1] = {0, 68}; //VK_D

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
    unsigned char* up[1];
    unsigned char* down[1];
    unsigned char* left[1];
    unsigned char* right[1];
    unsigned char* jump[1];
    unsigned char* run[1];
    unsigned char* dropitem[1];
    unsigned char* pause[1];
    unsigned char* altjump[1];
    unsigned char* altrun[1];
    unsigned char* special[1];

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
        unsigned char* up[1] = {0, 0};
        unsigned char* down[1] = {0, 0};
        unsigned char* left[1] = {0, 0};
        unsigned char* right[1] = {0, 0};
        unsigned char* jump[1] = {0, 0};
        unsigned char* run[1] = {0, 0};
        unsigned char* dropitem[1] = {0, 0};
        unsigned char* pause[1] = {0, 0};
        unsigned char* altjump[1] = {0, 0};
        unsigned char* altrun[1] = {0, 0};
        unsigned char* special[1] = {0, 0};

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

class PlayerInput {
    public:
        PlayerInput();
        ~PlayerInput();

        int GetKeyboardInput(uint32_t virtKey, int keyboardIdx);

        void Toggle(bool enable);
        void Update();
};

#endif
