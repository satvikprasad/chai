#pragma once

#include "cstate.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

void CDrawLine(CState *state, HMM_Vec2 vertices[2], Color color);
void CDrawLineInBounds(CState *state, HMM_Vec2 vertices[2], HMM_Vec4 bounds, Color color);
void CDrawRectangle(CState *state, HMM_Vec4 bounds, Color color);
void CDrawRectangleLines(CState *state, HMM_Vec4 bounds, Color color);
void CDrawText(CState *state, HMM_Vec2 position, const char *text, u32 font_size, Color color);
