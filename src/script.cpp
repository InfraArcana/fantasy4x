#include "script.hpp"

#include "io.hpp"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace script
{

namespace
{

lua_State* lua_state_ = nullptr;

const std::string script_dir = "scripts";

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    // Init Lua
    lua_state_ = luaL_newstate();
    luaL_openlibs(lua_state_);

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    lua_close(lua_state_);

    TRACE_FUNC_END;
}

void load(const std::string script)
{
    const std::string path = script_dir + "/" + script;

    TRACE << "Loading script: " << path << std::endl;

    if (
        luaL_loadfile   (lua_state_, path.c_str()) ||
        lua_pcall       (lua_state_, 0, 0, 0))
    {
        TRACE << "Failed to run script: " << path << std::endl
              << lua_tostring(lua_state_, -1) << std::endl;
        assert(false);
    }
}

//---------------------------------------------------------- Read integer
int get_int(const std::string& name)
{
    lua_getglobal(lua_state_, name.c_str());

    if (!lua_isinteger(lua_state_, -1))
    {
        TRACE << "\"" + name + "\" should be a number" << std::endl;
        assert(false);
    }

    // Take the returned value out of the stack
    // TODO: Should this be done?
    //lua_pop(L, 1)

    return lua_tointeger(lua_state_, -1);
}

//---------------------------------------------------------- Read string
std::string get_str(const std::string& name)
{
    lua_getglobal(lua_state_, name.c_str());

    if (!lua_isstring(lua_state_, -1))
    {
        TRACE << "\"" + name + "\" should be a string" << std::endl;
        assert(false);
    }

    // Take the returned value out of the stack
    // TODO: Should this be done?
    //lua_pop(L, 1)

    return lua_tostring(lua_state_, -1);
}

//---------------------------------------------------------- Read X, Y
P get_xy(const std::string& name)
{
    lua_getglobal(lua_state_, name.c_str());

    if (!lua_istable(lua_state_, -1))
    {
        TRACE << "\"" + name + "\" should be a table" << std::endl;
        assert(false);
    }

    P ret;

    ret.x = getfield("x");
    ret.y = getfield("y");

    return ret;
}

} // script
