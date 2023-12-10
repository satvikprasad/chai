#pragma once

#include "cstate.h"

void InitialiseScripting(CState *state);
void ScriptingConfigure(CState *state);
void ScriptingDestroy(CState *state);

void ScriptingPushFunc(CState *state, const char *func);
void ScriptingPushCState(CState *state);
HMM_Vec2 *ScriptingPopVertices(lua_State *L, u32 *vertex_count);

void ScriptingExecFuncReg(lua_State *L, i32 func, i32 nargs, i32 nret);
