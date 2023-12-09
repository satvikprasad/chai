#pragma once

#include "cstate.h"
#include "defines.h"
#include "vendor/HandmadeMath.h"

typedef struct CanvasLine {
	HMM_Vec2 vertices[2];
} CanvasLine;

typedef struct Canvas {
    HMM_Vec4 screen_bounds;

	HMM_Vec2 center;
	HMM_Vec2 size;

	CanvasLine *lines;
	u32 line_count;

    u32 index;
} Canvas;

void CanvasRender(CState *state, Canvas *canvas);
void CanvasUpdate(CState *state, Canvas *canvas);
void CanvasAddLine(Canvas *canvas, HMM_Vec2 vertices[2]);
