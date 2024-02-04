#include "../SMBXInternal/Reconstructed/PlayerInput.h"

#define FFI_EXPORT(sig) __declspec(dllexport) sig __cdecl

extern "C" {
    FFI_EXPORT(bool) LunaLuaIsPlayerPressingSpecialKey(int playerIdx)
    {
        return playerSpecialKeyPressed[playerIdx - 1];
    }
}
