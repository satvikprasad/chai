#include "cstate.h"
#include "raylib.h"
#include "scripting.h"
#include "util.h"
#include "vendor/HandmadeMath.h"

int main(void) {
    CState *state = CreateCState((HMM_Vec2){1280, 720});

    InitWindow(state->window_size.Width, state->window_size.Height, "Chai");

    SetTargetFPS(144);

	InitialiseScripting(state);

	ScriptingConfigure(state);

	PrintVec4(state->bg_color);

    while (!WindowShouldClose()) {
        CStateUpdate(state);

        BeginDrawing();

        ClearBackground((Color){state->bg_color.R, state->bg_color.G, state->bg_color.B, state->bg_color.A});
        CStateRender(state);

        EndDrawing();
    }

    CloseWindow();
	CStateDestroy(state);

    return 0;
}
