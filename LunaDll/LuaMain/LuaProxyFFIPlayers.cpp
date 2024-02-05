#include "../SMBXInternal/Reconstructed/PlayerInput.h"
#include "../Globals.h"

#define FFI_EXPORT(sig) __declspec(dllexport) sig __cdecl

extern "C" {

    FFI_EXPORT(void) LunaLuaTogglePlayerKeyOverhaul(bool value)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.Toggle(value);
    }
    FFI_EXPORT(bool) LunaLuaIsPlayerKeyOverhaulOn()
    {
        return gPlayerInputOverhaulToggled;
    }

    //Special Key functions
    FFI_EXPORT(bool) LunaLuaIsPlayerPressingSpecialKey(int playerIdx)
    {
        return playerSpecialKeyPressed[playerIdx - 1];
    }
    FFI_EXPORT(void) LunaLuaSetPlayerPressingSpecialKey(int playerIdx, bool value)
    {
        playerSpecialKeyPressed[playerIdx - 1] = value;
    }
    
    //Input Configuration
    FFI_EXPORT(void) LunaLuaChangePlayerKeysKeyboard(int type, int playerIdx, int virtKey, int keyboardIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetKeyboardControls(type, playerIdx, virtKey, keyboardIdx);
    }
    FFI_EXPORT(void) LunaLuaChangePlayerKeysController(int type, int playerIdx, int controllerIdx, int controllerID)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetControllerControls(type, playerIdx, controllerIdx, controllerID);
    }

    FFI_EXPORT(bool) LunaLuaIsPlayerPressing(int type, int playerIdx)
    {
        PlayerInput playerInputFunc;
        return playerInputFunc.IsPressing(type, playerIdx);
    }
    
    //Controller/Keyboard Changing
    FFI_EXPORT(void) LunaLuaChangePlayerKeyboard(int playerIdx, int keyboardIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetKeyboardIdx(playerIdx, keyboardIdx);
    }
    FFI_EXPORT(void) LunaLuaChangePlayerController(int playerIdx, int controllerIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetControllerIdx(playerIdx, controllerIdx);
    }
    FFI_EXPORT(void) LunaLuaResetAllPlayerInputs()
    {
        PlayerInput playerInputFunc;
        playerInputFunc.ResetAllInputs();
    }
}
