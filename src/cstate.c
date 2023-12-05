#include "cstate.h"
#include "canvas.h"
#include "defines.h"
#include "raylib.h"
#include "renderer.h"
#include "util.h"
#include "vendor/HandmadeMath.h"

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
    state->mouse_pos.Y = state->window_size.Y - GetMouseY();
    state->mouse_pos.X = GetMouseX();

    for (u32 i = 0; i < state->canvas_count; ++i) {
        Canvas *canvas = &state->canvases[i];

        CanvasUpdate(state, canvas);
    }
}

void CStateRender(CState *state) {
    for (u32 i = 0; i < state->canvas_count; ++i) {
        Canvas *canvas = &state->canvases[i];

        CanvasRender(state, canvas);
    }
}

void CStateDestroy(CState *state) {
	free(state->canvases);
	free(state);
}

static inline void PushCanvas(CState *state, Canvas canvas) {
    state->canvases[state->canvas_count++] = canvas;
}
