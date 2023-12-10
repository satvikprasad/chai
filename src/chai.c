#include "appstate.h"
#include "canvas.h"
#include "lauxlib.h"
#include "raylib.h"
#include "renderer.h"
#include "scripting.h"
#include "vendor/HandmadeMath.h"
#include "util.h"
#include <stdlib.h>

static inline AppState *CreateAppState(HMM_Vec2 window_size);
static inline void AppStateUpdate(AppState *state);
static inline void AppStateRender(AppState *state);
static inline void AppStateDestroy(AppState *state);
static inline void PushCanvas(AppState *state, Canvas canvas);

static inline void LoadFonts(AppState *state) {
	state->font = LoadFontEx("./assets/liberation-mono.ttf", 14, NULL, 0);
	SetTextureFilter(state->font.texture, TEXTURE_FILTER_BILINEAR);
}

int main(void) {
    AppState *state = CreateAppState((HMM_Vec2){1280, 720});

    InitWindow(state->window_size.Width, state->window_size.Height, "Chai");
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	LoadFonts(state);

    SetTargetFPS(144);

	InitialiseScripting(state);
	ScriptingConfigure(state);

    while (!WindowShouldClose()) {
        AppStateUpdate(state);

        BeginDrawing();

        ClearBackground((Color){state->bg_color.R, state->bg_color.G, state->bg_color.B, state->bg_color.A});
        AppStateRender(state);

        EndDrawing();
    }

	DumpProcedures(state);

    CloseWindow();
	AppStateDestroy(state);

    return 0;
}

static inline AppState *CreateAppState(HMM_Vec2 window_size) {
    AppState *state = malloc(sizeof(AppState));
    *state = (AppState){0};

    state->window_size = window_size;

    state->canvases = calloc(32, sizeof(Canvas));
    PushCanvas(state, (Canvas){
			.index = 0,
			.screen_bounds = (HMM_Vec4){10, 10, state->window_size.Width/2 - 10, 
			state->window_size.Height - 10},
			.center={0, 0},
			.size={100, 100}});
    PushCanvas(state, (Canvas){
			.index = 1,
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

static inline void AppStateUpdate(AppState *state) {
    state->mouse_pos = (HMM_Vec2){GetMouseX(), state->window_size.Y - GetMouseY()};
	state->mouse_delta = (HMM_Vec2){GetMouseDelta().x, -GetMouseDelta().y};

    for (u32 i = 0; i < state->canvas_count; ++i) {
        Canvas *canvas = &state->canvases[i];

        CanvasUpdate(state, canvas);
    }

	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure *proc = &state->procedures[i];

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && V2InBounds(state->mouse_pos, (HMM_Vec4){45, 20 + 20*i - 13, 50 + 100, 23 + 20*i})) {
			ScriptingExecFuncReg(state->lua, proc->func, 0, 1);

			u32 vertex_count;
			HMM_Vec2 *vertices = ScriptingPopVertices(state->lua, &vertex_count);

			for (u32 i = 1; i < vertex_count; ++i) {
				CanvasAddLine(&state->canvases[state->selected_canvas], (HMM_Vec2[2]){
					vertices[i-1],
					vertices[i]
				});
			}
		}
	}

	for (u32 i = 0; i < RegisteredEventTypeCount; ++i) {
		if (state->event_registry[i].registered) {
			ScriptingExecFuncReg(state->lua, state->event_registry[i].func, 0, 0);
		}
	}
}

static inline void AppStateRender(AppState *state) {
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

static inline void AppStateDestroy(AppState *state) {
	for (u32 i = 0; i < state->canvas_count; ++i) {
		Canvas *canvas = &state->canvases[i];

		free(canvas->lines);
	}

	free(state->canvases);

	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure *proc = &state->procedures[i];

		free(proc->name);

		luaL_unref(state->lua, LUA_REGISTRYINDEX, proc->func);
	}

	for (u32 i = 0; i < RegisteredEventTypeCount; ++i) {
		if (state->event_registry[i].registered) {
			luaL_unref(state->lua, LUA_REGISTRYINDEX, state->event_registry[i].func);
		}
	}

	free(state->procedures);

	free(state);
}

static inline void PushCanvas(AppState *state, Canvas canvas) {
    state->canvases[state->canvas_count++] = canvas;
}
