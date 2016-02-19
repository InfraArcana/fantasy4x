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

#ifdef NDEBUG
const std::string script_dir = "scripts";
#else
const std::string script_dir = "../scripts";
#endif

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

//    luaopen_base(lua_state_);
//    luaopen_io(lua_state_);
//    luaopen_string(lua_state_);
//    luaopen_math(lua_state_);

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

    if (
        luaL_loadfile   (lua_state_, path.c_str()) ||
        lua_pcall       (lua_state_, 0, 0, 0))
    {
        TRACE << "Failed to run script: " << path << std::endl
              << lua_tostring(lua_state_, -1) << std::endl;
        assert(false);
    }
}

int get_int(const std::string name)
{
    lua_getglobal(lua_state_, name.c_str());

    if (!lua_isinteger(lua_state_, -1))
    {
        TRACE << "\"" + name + "\" should be a number" << std::endl;
        assert(false);
    }

    // Take the returned value out of the stack
    //lua_pop(L, 1)

    return lua_tointeger(lua_state_, -1);
}

std::string get_str(const std::string name)
{
    lua_getglobal(lua_state_, name.c_str());

    if (!lua_isstring(lua_state_, -1))
    {
        TRACE << "\"" + name + "\" should be a string" << std::endl;
        assert(false);
    }

    // Take the returned value out of the stack
    //lua_pop(L, 1)

    return lua_tostring(lua_state_, -1);
}

} // script
