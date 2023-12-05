#include "cstate.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

int main(void) {
    CState *state = CreateCState((HMM_Vec2){1280, 720});

    InitWindow(state->window_size.Width, state->window_size.Height, "Chai");

    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        CStateUpdate(state);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        CStateRender(state);

        EndDrawing();
    }

    CloseWindow();
	CStateDestroy(state);

    return 0;
}
