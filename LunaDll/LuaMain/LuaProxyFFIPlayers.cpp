#include "../SMBXInternal/Reconstructed/PlayerInput.h"
#include "../Globals.h"

#define FFI_EXPORT(sig) __declspec(dllexport) sig __cdecl

extern "C" {
    // Toggles the player key overhaul on or off
    FFI_EXPORT(void) LunaLuaTogglePlayerKeyOverhaul(bool value)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.Toggle(value);
    }

    // Is the overhaul on?
    FFI_EXPORT(bool) LunaLuaIsPlayerKeyOverhaulOn()
    {
        return gPlayerInputOverhaulToggled;
    }

    // Input configuration (Keyboard)
    FFI_EXPORT(void) LunaLuaChangePlayerKeysKeyboard(int type, int playerIdx, int virtKey)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetKeyboardControls(type, playerIdx, virtKey);
    }

    // Input configuration (Controller)
    FFI_EXPORT(void) LunaLuaChangePlayerKeysController(int type, int playerIdx, int controllerIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetControllerControls(type, playerIdx, controllerIdx);
    }

    // Input keyboard idx changing
    FFI_EXPORT(void) LunaLuaChangePlayerKeyboard(int playerIdx, int keyboardIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetKeyboardIdx(playerIdx, keyboardIdx);
    }

    // Input controller idx changing
    FFI_EXPORT(void) LunaLuaChangePlayerController(int playerIdx, int controllerIdx)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetControllerIdx(playerIdx, controllerIdx);
    }

    // Is the player pressing a key?
    FFI_EXPORT(bool) LunaLuaIsPlayerPressing(int type, int playerIdx)
    {
        PlayerInput playerInputFunc;
        return playerInputFunc.IsPressing(type, playerIdx);
    }
    // Set a players key with this
    FFI_EXPORT(void) LunaLuaSetPlayerPressing(int type, int playerIdx, bool value)
    {
        PlayerInput playerInputFunc;
        playerInputFunc.SetPressing(type, playerIdx, value);
    }

    // Reset all inputs
    FFI_EXPORT(void) LunaLuaResetAllPlayerInputs()
    {
        PlayerInput playerInputFunc;
        playerInputFunc.ResetAllInputs();
    }
}
