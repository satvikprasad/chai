#pragma once

#include "cstate.h"
#include "defines.h"
#include "vendor/HandmadeMath.h"

typedef struct Canvas {
    HMM_Vec4 screen_bounds;

	HMM_Vec2 center;
	HMM_Vec2 canvas_size;

    u32 index;
} Canvas;

void CanvasRender(CState *state, Canvas *canvas);
void CanvasUpdate(CState *state, Canvas *canvas);
