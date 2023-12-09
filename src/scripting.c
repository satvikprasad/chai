#include "scripting.h"
#include "cstate.h"
#include "util.h"
#include "vendor/HandmadeMath.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline HMM_Vec4 DecodeTableV4(lua_State *lua);

static inline int AddProcedure(lua_State *L);

void InitialiseScripting(CState *state) {
	char buf[256];
	state->lua = luaL_newstate();
	luaL_openlibs(state->lua);

	lua_newtable(state->lua);
	{
		lua_pushstring(state->lua, "procedures");
		lua_newtable(state->lua);
		{
			lua_pushstring(state->lua, "add");
			lua_pushcfunction(state->lua, AddProcedure);
			lua_settable(state->lua, -3);
		}
		lua_settable(state->lua, -3);

		lua_pushstring(state->lua, "state");
		ScriptingPushCState(state);
		lua_settable(state->lua, -3);
	}
	lua_setglobal(state->lua, "Chai");

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

void ScriptingDestroy(CState *state) {
	lua_close(state->lua);
}

void ScriptingPushFunc(CState *state, const char *func) {
	lua_getglobal(state->lua, func);
}

void ScriptingPushCState(CState *state) {
	u32 bytes = sizeof(CState *);
	CState **p_state = (CState **)lua_newuserdata(state->lua, bytes);
	*p_state = state;
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

static int AddProcedure(lua_State *L) {
	CState *state = *((CState **)lua_touserdata(L, 1));

	const char *func = lua_tostring(L, 2);
	const char *name = lua_tostring(L, 3);
	
	state->procedures = realloc(state->procedures, sizeof(Procedure) * ++state->procedure_count);
	Procedure *proc = &state->procedures[state->procedure_count-1];

	proc->func = malloc(sizeof(char) * strlen(func));
	proc->name = malloc(sizeof(char) * strlen(name));

	strcpy(proc->func, func);
	strcpy(proc->name, name);

	return 0;	
}
