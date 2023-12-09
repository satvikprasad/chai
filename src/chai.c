#include "cstate.h"
#include "raylib.h"
#include "scripting.h"
#include "vendor/HandmadeMath.h"
#include "util.h"

static inline void LoadFonts(CState *state) {
	state->font = LoadFontEx("./assets/liberation-mono.ttf", 14, NULL, 0);
	SetTextureFilter(state->font.texture, TEXTURE_FILTER_BILINEAR);
}

int main(void) {
    CState *state = CreateCState((HMM_Vec2){1280, 720});

    InitWindow(state->window_size.Width, state->window_size.Height, "Chai");
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	LoadFonts(state);

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

	DumpProcedures(state);

    CloseWindow();
	CStateDestroy(state);

    return 0;
}
