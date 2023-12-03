#include "cstate.h"
#include "canvas.h"
#include "defines.h"
#include "raylib.h"
#include "renderer.h"
#include "vendor/HandmadeMath.h"

#include <stdlib.h>

static inline void PushCanvas(CState *state, Canvas canvas);

CState *CreateCState(HMM_Vec2 window_size) {
    CState *state = malloc(sizeof(CState));
    *state = (CState){0};

    state->window_size = window_size;

    state->canvases = calloc(32, sizeof(Canvas));
    PushCanvas(state, (Canvas){.screen_bounds = (HMM_Vec4){500, 50, 800, 700},
			.center={0, 0},
			.canvas_size={100, 100}});

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

static inline void PushCanvas(CState *state, Canvas canvas) {
    state->canvases[state->canvas_count++] = canvas;
}
