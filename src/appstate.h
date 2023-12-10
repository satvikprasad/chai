#pragma once

#include "defines.h"
#include "lua.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

typedef struct Procedure {
	i32 func;
	char *name;
} Procedure;

typedef enum {
	RegisteredEventType_UPDATE = 0,
	RegisteredEventType_RENDER,
	RegisteredEventTypeCount,
} RegisteredEventType;

typedef struct AppState {
	Font font;

    HMM_Vec2 window_size;

	HMM_Vec4 bg_color;

    HMM_Vec2 mouse_pos;
	HMM_Vec2 mouse_delta;

    struct Canvas *canvases;
    u32 canvas_count;
	u32 selected_canvas;

	Procedure *procedures;
	u32 procedure_count;

	lua_State *lua;

	struct {
		i32 func;
		b8 registered;
	} event_registry[8];
} AppState;
