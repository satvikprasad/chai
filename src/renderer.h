#pragma once

#include "appstate.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

void CDrawLine(AppState *state, HMM_Vec2 vertices[2], Color color);
void CDrawLineInBounds(AppState *state, HMM_Vec2 vertices[2], HMM_Vec4 bounds, Color color);
void CDrawRectangle(AppState *state, HMM_Vec4 bounds, Color color);
void CDrawRectangleLines(AppState *state, HMM_Vec4 bounds, Color color);
void CDrawText(AppState *state, HMM_Vec2 position, const char *text, u32 font_size, Color color);
