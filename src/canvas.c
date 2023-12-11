#include "canvas.h"
#include "renderer.h"
#include "raylib.h"
#include "util.h"
#include "vendor/HandmadeMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline HMM_Vec2 ScreenSpaceToCanvasSpace(AppState *state, Canvas *canvas, HMM_Vec2 vec);
static inline HMM_Vec2 CanvasSpaceToScreenSpace(AppState *state, Canvas *canvas, HMM_Vec2 vec);

static inline void HandleInputs(AppState *state, Canvas *canvas);

void CanvasUpdate(AppState *state, Canvas *canvas) {
	HandleInputs(state, canvas);

	HMM_Vec2 scale = HMM_DivV2(HMM_SubV2(canvas->screen_bounds.ZW, canvas->screen_bounds.XY), canvas->size);
	HMM_Vec2 screen_d_axis = HMM_MulV2(scale, canvas->d_axis);

	printf("%f\n", screen_d_axis.Y);

	if (screen_d_axis.Y > 100) {
		canvas->d_axis.Y /= 2;
	}

	if (screen_d_axis.Y < 25) {
		canvas->d_axis.Y *= 2;
	}
}

void CanvasRender(AppState *state, Canvas *canvas) {
    CDrawRectangle(state, canvas->screen_bounds, RAYWHITE);

	{
		HMM_Vec4 bounds;
		bounds.XY = ClampV2ToBounds(CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){0, 0}), 
				canvas->screen_bounds);
		bounds.ZW = ClampV2ToBounds(CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){10, 10}), 
				canvas->screen_bounds);

		CDrawRectangle(state, bounds, BLACK);
	}

	for (u32 i = 0; i < canvas->line_count; ++i) {
		CanvasLine *line = &canvas->lines[i];

		HMM_Vec2 screen_vertices[2] = {
					CanvasSpaceToScreenSpace(state, canvas, line->vertices[0]),
					CanvasSpaceToScreenSpace(state, canvas, line->vertices[1])
				};


		CDrawLineInBounds(state, screen_vertices, canvas->screen_bounds, BLACK);
	}

	Color color = BLACK;
	if (canvas->index == state->selected_canvas) color = RED;

    CDrawRectangleLines(state, canvas->screen_bounds, color);

	i32 start = FloorToI32(canvas->center.Y - canvas->size.Height/2, canvas->d_axis.Y);
	for (i32 i = start; i < canvas->center.Y + canvas->size.Height/2; i+=canvas->d_axis.Y) {
		HMM_Vec2 v = HMM_V2(0, i);
		f32 y = CanvasSpaceToScreenSpace(state, canvas, v).Y;

		CDrawLine(state, (HMM_Vec2[2]){HMM_V2(canvas->screen_bounds.XY.X, y), HMM_V2(canvas->screen_bounds.ZW.X, y)}, GRAY);
	}
}

void CanvasAddLine(Canvas *canvas, HMM_Vec2 vertices[2]) {
	canvas->lines = realloc(canvas->lines, sizeof(CanvasLine)*++canvas->line_count);

	memcpy(canvas->lines[canvas->line_count -1].vertices, vertices, sizeof(HMM_Vec2)*2);
}

static inline HMM_Vec2 CanvasSpaceToScreenSpace(AppState *state, Canvas *canvas, HMM_Vec2 vec) {
	HMM_Vec2 canvas_screen_size = {canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X, 
		canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y};

	HMM_Mat2 scale = {{{canvas_screen_size.Width / canvas->size.Width, 0}, {0, canvas_screen_size.Height / canvas->size.Height}}};

	HMM_Vec2 from_center = HMM_MulM2V2(scale, HMM_SubV2(vec, canvas->center));

	return HMM_AddV2(HMM_DivV2F(HMM_AddV2(canvas->screen_bounds.XY, canvas->screen_bounds.ZW), 
				2), from_center);
}

static inline HMM_Vec2 ScreenSpaceToCanvasSpace(AppState *state, Canvas *canvas, HMM_Vec2 vec) {
	HMM_Vec2 canvas_screen_size = {canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X, 
		canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y};

	HMM_Mat2 scale = {{{canvas->size.Width / canvas_screen_size.Width, 0}, {0, canvas->size.Height / canvas_screen_size.Height}}};

	HMM_Vec2 from_center = HMM_SubV2(vec, HMM_DivV2F(HMM_AddV2(canvas->screen_bounds.XY,
					canvas->screen_bounds.ZW), 2));


	return HMM_AddV2(HMM_MulM2V2(scale, from_center), canvas->center);
}

static inline void HandleInputs(AppState *state, Canvas *canvas) {
	if (canvas->index != state->selected_canvas) {
		if (V2InBounds(state->mouse_pos, canvas->screen_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			state->selected_canvas = canvas->index;
		} 
		return;
	}

	if (IsKeyDown(KEY_A)) {
		CanvasAddLine(canvas, (HMM_Vec2[2]){(HMM_Vec2){10, 10}, ScreenSpaceToCanvasSpace(state, canvas, state->mouse_pos)});
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

