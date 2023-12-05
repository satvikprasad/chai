#pragma once

#include "defines.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

typedef struct CState {
    HMM_Vec2 window_size;
    HMM_Vec2 mouse_pos;

    struct Canvas *canvases;
    u32 canvas_count;
} CState;

CState *CreateCState(HMM_Vec2 window_size);

void CStateUpdate(CState *state);
void CStateRender(CState *state);

void CStateDestroy(CState *state);
