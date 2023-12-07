#pragma once

#include "defines.h"
#include "lua.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

typedef struct CState {
    HMM_Vec2 window_size;

	HMM_Vec4 bg_color;

    HMM_Vec2 mouse_pos;
	HMM_Vec2 mouse_delta;

    struct Canvas *canvases;
    u32 canvas_count;

	lua_State *lua;
} CState;

CState *CreateCState(HMM_Vec2 window_size);

void CStateUpdate(CState *state);
void CStateRender(CState *state);

void CStateDestroy(CState *state);
