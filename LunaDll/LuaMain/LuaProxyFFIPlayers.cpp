#include "../SMBXInternal/Reconstructed/PlayerInput.h"
#include "../Globals.h"

#define FFI_EXPORT(sig) __declspec(dllexport) sig __cdecl

extern "C" {
    // Toggles the player keys on or off
    FFI_EXPORT(void) LunaLuaTogglePlayerKeys(bool value)
    {
        gPlayerInput.Toggle(value);
    }

    // Are the keys on?
    FFI_EXPORT(bool) LunaLuaIsPlayerKeysOn()
    {
        return gPlayerInputOverhaulToggled;
    }

    // Input configuration (Keyboard)
    FFI_EXPORT(void) LunaLuaChangePlayerKeysKeyboard(int type, int playerIdx, int virtKey)
    {
        gPlayerInput.SetKeyboardControls(type, playerIdx, virtKey);
    }

    // Input configuration (Controller)
    FFI_EXPORT(void) LunaLuaChangePlayerKeysController(int type, int playerIdx, int controllerIdx)
    {
        gPlayerInput.SetControllerControls(type, playerIdx, controllerIdx);
    }

    // Input keyboard idx changing
    FFI_EXPORT(void) LunaLuaChangePlayerKeyboard(int playerIdx, int keyboardIdx)
    {
        gPlayerInput.SetKeyboardIdx(playerIdx, keyboardIdx);
    }

    // Input controller idx changing
    FFI_EXPORT(void) LunaLuaChangePlayerController(int playerIdx, int controllerIdx)
    {
        gPlayerInput.SetControllerIdx(playerIdx, controllerIdx);
    }

    // Is the player pressing a key?
    FFI_EXPORT(bool) LunaLuaGetPlayerPressing(int type, int playerIdx)
    {
        return gPlayerInput.IsPressing(type, playerIdx);
    }
    // Set a players key pressing state with this
    FFI_EXPORT(void) LunaLuaSetPlayerPressing(int type, int playerIdx, bool value)
    {
        gPlayerInput.SetPressing(type, playerIdx, value);
    }

    // Reset all inputs. Only called starting the engine when inputs.ini doesn't exist
    FFI_EXPORT(void) LunaLuaResetAllPlayerInputs()
    {
        gPlayerInput.ResetAllInputs();
    }
    // Refresh all inputs. If readInputs is on, it'll read all the inputs from inputs.ini. Or if isWritten is on, input data set will be saved to inputs.ini.
    FFI_EXPORT(void) LunaLuaRefreshAllPlayerInputs(bool readInputs, bool isWritten)
    {
        gPlayerInput.RefreshAllInputs(isWritten, readInputs);
    }
}
