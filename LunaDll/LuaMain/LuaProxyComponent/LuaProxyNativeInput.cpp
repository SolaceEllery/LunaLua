#include "../LuaProxy.h"

#include "../../SMBXInternal/NativeInput.h"
#include "../../Defines.h"
#include "../../SMBXInternal/Reconstructed/PlayerInput.h"

#pragma warning(disable: 4800)

LuaProxy::InputConfig::InputConfig(unsigned short index) : m_index(index)
{}

int LuaProxy::InputConfig::idx() const
{
    return m_index;
}

short LuaProxy::InputConfig::inputType(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    else
        return g_playerInputPressing[m_index - 1].currentInputType;
}

void LuaProxy::InputConfig::setInputType(short inputType, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    g_playerInputPressing[m_index - 1].currentInputType = inputType;
}


short LuaProxy::InputConfig::up(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].up;
    else
        return g_playerControllerInputs[m_index - 1].up;
    return 0;
}

short LuaProxy::InputConfig::down(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].down;
    else
        return g_playerControllerInputs[m_index - 1].down;
    return 0;
}

short LuaProxy::InputConfig::left(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].left;
    else
        return g_playerControllerInputs[m_index - 1].left;
    return 0;
}

short LuaProxy::InputConfig::right(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].right;
    else
        return g_playerControllerInputs[m_index - 1].right;
    return 0;
}

short LuaProxy::InputConfig::run(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].run;
    else
        return g_playerControllerInputs[m_index - 1].run;
}

short LuaProxy::InputConfig::altrun(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].altrun;
    else
        return g_playerControllerInputs[m_index - 1].altrun;
}

short LuaProxy::InputConfig::jump(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].jump;
    else
        return g_playerControllerInputs[m_index - 1].jump;
}

short LuaProxy::InputConfig::altjump(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].altjump;
    else
        return g_playerControllerInputs[m_index - 1].altjump;
}

short LuaProxy::InputConfig::dropitem(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].dropitem;
    else
        return g_playerControllerInputs[m_index - 1].dropitem;
}

short LuaProxy::InputConfig::pause(lua_State* L)
{
    if (!isValid_throw(L))
        return 0;
    if (inputType(L) == 0)
        return g_playerKeyboardInputs[m_index - 1].pause;
    else
        return g_playerControllerInputs[m_index - 1].pause;
}


void LuaProxy::InputConfig::setUp(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].up = keycode;
    else
        g_playerControllerInputs[m_index - 1].up = keycode;
}


void LuaProxy::InputConfig::setDown(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
        if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].down = keycode;
    else
        g_playerControllerInputs[m_index - 1].down = keycode;
}

void LuaProxy::InputConfig::setLeft(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].left = keycode;
    else
        g_playerControllerInputs[m_index - 1].left = keycode;
}

void LuaProxy::InputConfig::setRight(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].right = keycode;
    else
        g_playerControllerInputs[m_index - 1].right = keycode;
}

void LuaProxy::InputConfig::setRun(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].run = keycode;
    else
        g_playerControllerInputs[m_index - 1].run = keycode;
}

void LuaProxy::InputConfig::setAltRun(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].altrun = keycode;
    else
        g_playerControllerInputs[m_index - 1].altrun = keycode;
}

void LuaProxy::InputConfig::setJump(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].jump = keycode;
    else
        g_playerControllerInputs[m_index - 1].jump = keycode;
}

void LuaProxy::InputConfig::setAltJump(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].altjump = keycode;
    else
        g_playerControllerInputs[m_index - 1].altjump = keycode;
}

void LuaProxy::InputConfig::setDropItem(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].dropitem = keycode;
    else
        g_playerControllerInputs[m_index - 1].dropitem = keycode;
}

void LuaProxy::InputConfig::setPause(unsigned short keycode, lua_State* L)
{
    if (!isValid_throw(L))
        return;
    if (inputType(L) == 0)
        g_playerKeyboardInputs[m_index - 1].pause = keycode;
    else
        g_playerControllerInputs[m_index - 1].pause = keycode;
}


bool LuaProxy::InputConfig::isValid() const
{
    return (m_index >= 1 && m_index <= 200);
}


bool LuaProxy::InputConfig::isValid_throw(lua_State *L) const
{
    if (!isValid()){
        luaL_error(L, "Invalid KeyboardConfig-Pointer");
        return false;
    }
    return true;
}
