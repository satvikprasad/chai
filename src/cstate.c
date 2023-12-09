#include "cstate.h"
#include "canvas.h"
#include "defines.h"
#include "lua.h"
#include "raylib.h"
#include "renderer.h"
#include "scripting.h"
#include "util.h"
#include "vendor/HandmadeMath.h"

#include <stdio.h>
#include <stdlib.h>

static inline void PushCanvas(CState *state, Canvas canvas);

CState *CreateCState(HMM_Vec2 window_size) {
    CState *state = malloc(sizeof(CState));
    *state = (CState){0};

    state->window_size = window_size;

    state->canvases = calloc(32, sizeof(Canvas));
    PushCanvas(state, (Canvas){
			.screen_bounds = (HMM_Vec4){10, 10, state->window_size.Width/2 - 10, 
			state->window_size.Height - 10},
			.center={0, 0},
			.size={100, 100}});
    PushCanvas(state, (Canvas){
			.screen_bounds = (HMM_Vec4){state->window_size.Width/2 + 10, 10, state->window_size.Width - 10, state->window_size.Height - 10},
			.center={0, 0},
			.size={100, 100}});

	for (i32 i = 0; i < 1000; ++i) {
		Canvas *canvas = &state->canvases[0];

		canvas->lines = realloc(canvas->lines, sizeof(CanvasLine)*++canvas->line_count);

		canvas->lines[canvas->line_count - 1].vertices[0] = (HMM_Vec2){(f32)(i-1)/10, (f32)(i-1)*(f32)(i-1)/10000};
		canvas->lines[canvas->line_count - 1].vertices[1] = (HMM_Vec2){(f32)i/10, (f32)i*(f32)i/10000};
	}

    return state;
}

void CStateUpdate(CState *state) {
    state->mouse_pos = (HMM_Vec2){GetMouseX(), state->window_size.Y - GetMouseY()};
	state->mouse_delta = (HMM_Vec2){GetMouseDelta().x, -GetMouseDelta().y};

    for (u32 i = 0; i < state->canvas_count; ++i) {
        Canvas *canvas = &state->canvases[i];

        CanvasUpdate(state, canvas);
    }

	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure *proc = &state->procedures[i];

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && V2InBounds(state->mouse_pos, (HMM_Vec4){45, 20 + 20*i - 13, 50 + 100, 23 + 20*i})) {
			ScriptingPushFunc(state, proc->func);
			lua_call(state->lua, 0, 0);
		}
	}

}

void CStateRender(CState *state) {
    for (u32 i = 0; i < state->canvas_count; ++i) {
        Canvas *canvas = &state->canvases[i];

        CanvasRender(state, canvas);
    }

	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure *proc = &state->procedures[i];

		HMM_Vec4 bounds = {45, 20 + 20*i - 13, 50 + 100, 23 + 20*i};
		Color color = WHITE;

		if (V2InBounds(state->mouse_pos, bounds)) {
			color = RED;
		}

		CDrawText(state, (HMM_Vec2){50, 20 + 20*i}, proc->name, 14, WHITE);
		CDrawRectangleLines(state, bounds, color);
	}
}

void CStateDestroy(CState *state) {
	free(state->canvases);
	free(state);
}

static inline void PushCanvas(CState *state, Canvas canvas) {
    state->canvases[state->canvas_count++] = canvas;
}
