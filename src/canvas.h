#pragma once

#include "appstate.h"
#include "defines.h"
#include "vendor/HandmadeMath.h"

typedef struct CanvasLine {
	HMM_Vec2 vertices[2];
} CanvasLine;

typedef struct Canvas {
    HMM_Vec4 screen_bounds;

	HMM_Vec2 center;
	HMM_Vec2 size;
	HMM_Vec2 d_axis;

	CanvasLine *lines;
	u32 line_count;

    u32 index;
} Canvas;

void CanvasRender(AppState *state, Canvas *canvas);
void CanvasUpdate(AppState *state, Canvas *canvas);
void CanvasAddLine(Canvas *canvas, HMM_Vec2 vertices[2]);
