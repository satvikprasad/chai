#include "scripting.h"
#include "cstate.h"
#include "util.h"
#include "vendor/HandmadeMath.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline HMM_Vec4 DecodeTableV4(lua_State *lua);

static inline int AddProcedure(lua_State *L);
static inline int RegisterEvent(lua_State *L);

void InitialiseScripting(CState *state) {
	char buf[256];
	state->lua = luaL_newstate();
	luaL_openlibs(state->lua);

	lua_newtable(state->lua);
	{
		lua_pushstring(state->lua, "event_types");
		lua_newtable(state->lua);
		{
			lua_pushstring(state->lua, "update");
			lua_pushnumber(state->lua, RegisteredEventType_UPDATE);
			lua_settable(state->lua, -3);
		}
		lua_settable(state->lua, -3);

		lua_pushstring(state->lua, "register_event");
		lua_pushcfunction(state->lua, RegisterEvent);
		lua_settable(state->lua, -3);

		lua_pushstring(state->lua, "add_proc");
		lua_pushcfunction(state->lua, AddProcedure);
		lua_settable(state->lua, -3);

		lua_pushstring(state->lua, "state");
		ScriptingPushCState(state);
		lua_settable(state->lua, -3);
	}
	lua_setglobal(state->lua, "Chai");

	if(0 != luaL_dofile(state->lua, "./lua/chai.lua")) {
		printf("Failed to load chai.lua!\n %s\n", lua_tostring(state->lua, -1));
		lua_close(state->lua);
	}
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

		lua_pop(state->lua, 1);
	}

	lua_pop(state->lua, 1);
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

HMM_Vec2 *ScriptingPopVertices(lua_State *L, u32 *vertex_count) {
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_geti(L, -1, 2);
	*vertex_count = (u32)lua_tonumber(L, -1);
	lua_pop(L, 1);

	HMM_Vec2 *vertices = calloc(*vertex_count, sizeof(HMM_Vec2));

	lua_geti(L, -1, 1);
	for (u32 i = 1; i <= *vertex_count; ++i) {
		lua_rawgeti(L, -1, i);
		{
			lua_rawgeti(L, -1, 1);
			vertices[i-1].X = lua_tonumber(L, -1);
			lua_pop(L, 1);

			lua_rawgeti(L, -1, 2);
			vertices[i-1].Y = lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	return vertices;
}

void ScriptingExecFuncReg(lua_State *L, i32 func, i32 nargs, i32 nret) {
	lua_rawgeti(L, LUA_REGISTRYINDEX, func);

	lua_call(L, nargs, nret);
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
	int func = luaL_ref(L, LUA_REGISTRYINDEX);
	const char *name = lua_tostring(L, -1);

	CState *state = *((CState **)lua_touserdata(L, -2));

	state->procedures = realloc(state->procedures, sizeof(Procedure) * ++state->procedure_count);
	Procedure *proc = &state->procedures[state->procedure_count-1];

	proc->func = func;
	proc->name = malloc(sizeof(char) * strlen(name));
	strcpy(proc->name, name);

	return 0;
}

static int RegisterEvent(lua_State *L) {
	int func = luaL_ref(L, LUA_REGISTRYINDEX);

	CState *state = *((CState **)lua_touserdata(L, -2));
	RegisteredEventType type = lua_tonumber(L, -1);

	state->event_registry[type].registered = true;
	state->event_registry[type].func = func;

	return 0;
}
