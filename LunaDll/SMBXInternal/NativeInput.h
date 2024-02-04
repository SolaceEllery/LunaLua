#ifndef Keyboard_hhhh
#define Keyboard_hhhh

#include "../Defines.h"

// Vkey table reference
// 0 - Up
// 1 - Down
// 2 - Left
// 3 - Right
// 4 - Run
// 5 - Alt run
// 6 - Jump
// 7 - Alt jump
// 8 - Drop item
// 9 - Pause
// 10 - Special (SMAS++)

struct NewSMBXInputKeyboard
{
    short up;
    short down;
    short left;
    short right;
    short jump;
    short run;
    short dropitem;
    short pause;
    short altjump;
    short altrun;
    short special;

    // Constructor
    NewSMBXInputKeyboard()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        short up = 38; //VK_UP
        short down = 40; //VK_DOWN
        short left = 37; //VK_LEFT
        short right = 39; //VK_RIGHT
        short jump = 90; //VK_Z
        short run = 88; //VK_X
        short dropitem = 16; //VK_SHIFT
        short pause = 27; //VK_ESCAPE
        short altjump = 65; //VK_A
        short altrun = 83; //VK_S
        short special = 68; //VK_D
    }
};

struct NewSMBXInputController
{
    short up;
    short down;
    short left;
    short right;
    short jump;
    short run;
    short dropitem;
    short pause;
    short altjump;
    short altrun;
    short special;

    // Constructor
    NewSMBXInputController()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        short up = 0;
        short down = 0;
        short left = 0;
        short right = 0;
        short jump = 0;
        short run = 0;
        short dropitem = 0;
        short pause = 0;
        short altjump = 0;
        short altrun = 0;
        short special = 0;
    }
};

namespace SMBXInput {
    
    /* Player Input type: 
     * 0 - Keyboard
     * 1 - Joystick #1
     * 2 - Joystick #2
     * ...
     * N - Joystick #N
     */
    static inline short getPlayerInputType(unsigned short index)
    {
        if (index < 1 || index > GM_MAX_CONTROLLABLE_PLAYERS) return -1;
        return GM_INPUTTYPE[index - 1];
    }

    static inline void setPlayerInputType(unsigned short index, short inputType)
    {
        if (index < 1 || index > GM_MAX_CONTROLLABLE_PLAYERS) return;
        GM_INPUTTYPE[index - 1] = inputType;
    }
}

#pragma pack(push, 1)
struct __declspec(align(1)) SMBXNativeKeyboard
{
    short up;
    short down;
    short left;
    short right;
    short jump;
    short run;
    short dropitem;
    short pause;
    short altjump;
    short altrun;
    //short special;

    static inline SMBXNativeKeyboard* Get(unsigned short inputIndex) {
        if (inputIndex < 1 || inputIndex > 2) return nullptr;
        return &((SMBXNativeKeyboard*)GM_VKEY_TABLE_PTR)[inputIndex - 1];
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct __declspec(align(1)) SMBXNativeJoystick
{
    short up;
    short down;
    short left;
    short right;
    short jump;
    short run;
    short dropitem;
    short pause;
    short altjump;
    short altrun;
    //short special;

    static inline SMBXNativeJoystick* Get(unsigned short inputIndex) {
        if (inputIndex < 1 || inputIndex > GM_MAX_CONTROLLABLE_PLAYERS) return nullptr;
        return &((SMBXNativeJoystick*)GM_VJOY_TABLE_PTR)[inputIndex - 1];
    }
};
#pragma pack(pop)



#endif
