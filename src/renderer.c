#include "renderer.h"
#include "cstate.h"
#include "vendor/HandmadeMath.h"

void CDrawRectangle(CState *state, HMM_Vec4 bounds, Color color) {
    DrawRectangleRec((Rectangle){bounds.XY.X, state->window_size.Y - bounds.ZW.Y,
                                 bounds.ZW.X - bounds.XY.X, bounds.ZW.Y - bounds.XY.Y},
                     BLACK);
}

void CDrawRectangleLines(CState *state, HMM_Vec4 bounds, Color color) {
    DrawRectangleLines(bounds.XY.X, state->window_size.Y - bounds.ZW.Y, bounds.ZW.X - bounds.XY.X,
                       bounds.ZW.Y - bounds.XY.Y, BLACK);
}

