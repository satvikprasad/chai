#pragma once

#include "appstate.h"

void InitialiseScripting(AppState *state);
void ScriptingConfigure(AppState *state);
void ScriptingDestroy(AppState *state);

void ScriptingPushFunc(AppState *state, const char *func);
void ScriptingPushAppState(AppState *state);
HMM_Vec2 *ScriptingPopVertices(lua_State *L, u32 *vertex_count);

void ScriptingExecFuncReg(lua_State *L, i32 func, i32 nargs, i32 nret);
