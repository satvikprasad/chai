#include "cstate.h"
#include "vendor/HandmadeMath.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

static inline HMM_Vec4 DecodeTableV4(lua_State *lua);

void InitialiseScripting(CState *state) {
	char buf[256];
	state->lua = luaL_newstate();
	luaL_openlibs(state->lua);

	luaL_dofile(state->lua, "./lua/chai.lua");
}

void ScriptingConfigure(CState *state) {
	lua_getglobal(state->lua, "Chai");
	if (!lua_istable(state->lua, -1)) {
		printf("Can't find table 'Chai'\n");
	}

	{
		lua_pushstring(state->lua, "bg");
		lua_gettable(state->lua, -2);

		{
			if (!lua_istable(state->lua, -1)) {
				printf("Can't find table 'Chai.bg'\n");
			}

			state->bg_color = DecodeTableV4(state->lua);
		}
	}
}

static inline HMM_Vec4 DecodeTableV4(lua_State *lua) {
	HMM_Vec4 vec;

	for (u32 i = 1; i <= 4; ++i) {
		lua_pushnumber(lua, i);
		lua_gettable(lua, -2);
		vec.Elements[i-1] = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
	}

	return vec;
}
