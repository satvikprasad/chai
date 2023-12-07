#include "canvas.h"
#include "renderer.h"
#include "raylib.h"
#include "util.h"
#include "vendor/HandmadeMath.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static inline HMM_Vec2 ScreenSpaceToCanvasSpace(CState *state, Canvas *canvas, HMM_Vec2 vec);
static inline HMM_Vec2 CanvasSpaceToScreenSpace(CState *state, Canvas *canvas, HMM_Vec2 vec);

static inline void HandleInputs(CState *state, Canvas *canvas);

void CanvasUpdate(CState *state, Canvas *canvas) {
	HandleInputs(state, canvas);
}

void CanvasRender(CState *state, Canvas *canvas) {

	HMM_Vec4 bounds;
	bounds.XY = ClampV2ToBounds(CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){0, 0}), 
			canvas->screen_bounds);
	bounds.ZW = ClampV2ToBounds(CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){10, 10}), 
			canvas->screen_bounds);

	CDrawRectangle(state, bounds, BLACK);

	for (u32 i = 0; i < canvas->line_count; ++i) {
		CanvasLine *line = &canvas->lines[i];

		HMM_Vec2 screen_vertices[2] = {
					CanvasSpaceToScreenSpace(state, canvas, line->vertices[0]),
					CanvasSpaceToScreenSpace(state, canvas, line->vertices[1])
				};


		CDrawLineInBounds(state, screen_vertices, canvas->screen_bounds, BLACK);
	}

    CDrawRectangleLines(state, canvas->screen_bounds, BLACK);
}

static inline HMM_Vec2 CanvasSpaceToScreenSpace(CState *state, Canvas *canvas, HMM_Vec2 vec) {
	HMM_Vec2 canvas_screen_size = {canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X, 
		canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y};

	HMM_Mat2 scale = {{{canvas_screen_size.Width / canvas->size.Width, 0}, {0, canvas_screen_size.Height / canvas->size.Height}}};

	HMM_Vec2 from_center = HMM_MulM2V2(scale, HMM_SubV2(vec, canvas->center));

	return HMM_AddV2(HMM_DivV2F(HMM_AddV2(canvas->screen_bounds.XY, canvas->screen_bounds.ZW), 
				2), from_center);
}

static inline HMM_Vec2 ScreenSpaceToCanvasSpace(CState *state, Canvas *canvas, HMM_Vec2 vec) {
	HMM_Vec2 canvas_screen_size = {canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X, 
		canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y};

	HMM_Mat2 scale = {{{canvas->size.Width / canvas_screen_size.Width, 0}, {0, canvas->size.Height / canvas_screen_size.Height}}};

	HMM_Vec2 from_center = HMM_SubV2(vec, HMM_DivV2F(HMM_AddV2(canvas->screen_bounds.XY,
					canvas->screen_bounds.ZW), 2));


	return HMM_AddV2(HMM_MulM2V2(scale, from_center), canvas->center);
}

static inline void HandleInputs(CState *state, Canvas *canvas) {
	if (IsKeyDown(KEY_A)) {
		canvas->lines = realloc(canvas->lines, sizeof(CanvasLine)*++canvas->line_count);

		canvas->lines[canvas->line_count - 1].vertices[0] = (HMM_Vec2){10, 10};
		canvas->lines[canvas->line_count - 1].vertices[1] = ScreenSpaceToCanvasSpace(state, canvas, state->mouse_pos);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		HMM_Mat2 scale = {{{
			canvas->size.Width / (canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X), 0
		}, {
			0, canvas->size.Height / (canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y),
		}}};

		canvas->center = HMM_AddV2(canvas->center, HMM_MulM2V2(scale, HMM_MulV2F(state->mouse_delta, -1)));
	}

	if (IsKeyDown(KEY_LEFT_CONTROL)) {
		canvas->size.X -= GetMouseWheelMove();
	}

	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		canvas->size.Y -= GetMouseWheelMove();
	}
}
