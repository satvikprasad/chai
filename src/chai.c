#include "cstate.h"
#include "raylib.h"
#include "scripting.h"
#include "vendor/HandmadeMath.h"
#include <stdio.h>

int main(void) {
    CState *state = CreateCState((HMM_Vec2){1280, 720});

    InitWindow(state->window_size.Width, state->window_size.Height, "Chai");

    SetTargetFPS(144);

	InitialiseScripting(state);
	ScriptingConfigure(state);

    while (!WindowShouldClose()) {
        CStateUpdate(state);

        BeginDrawing();

        ClearBackground((Color){state->bg_color.R, state->bg_color.G, state->bg_color.B, state->bg_color.A});
        CStateRender(state);

        EndDrawing();
    }

	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure proc = state->procedures[i];

		printf("Procedure %u: (%s, %s)\n", i, proc.func, proc.name);
	}

    CloseWindow();
	CStateDestroy(state);

    return 0;
}
