#pragma once

#include "defines.h"
#include "lua.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

typedef struct Procedure {
	i32 func;
	char *name;
} Procedure;

typedef struct CState {
	Font font;

    HMM_Vec2 window_size;

	HMM_Vec4 bg_color;

    HMM_Vec2 mouse_pos;
	HMM_Vec2 mouse_delta;

    struct Canvas *canvases;
    u32 canvas_count;

	int proc_table;

	Procedure *procedures;
	u32 procedure_count;

	lua_State *lua;
} CState;

CState *CreateCState(HMM_Vec2 window_size);

void CStateUpdate(CState *state);
void CStateRender(CState *state);

void CStateDestroy(CState *state);
