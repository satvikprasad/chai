#pragma once

#include "appstate.h"
#include "vendor/HandmadeMath.h"

void PrintVec2(HMM_Vec2 vec);
void PrintVec3(HMM_Vec3 vec);
void PrintVec4(HMM_Vec4 vec);

HMM_Vec2 ClampV2ToBounds(HMM_Vec2 vec, HMM_Vec4 bounds);
b8 V2InBounds(HMM_Vec2 vec, HMM_Vec4 bounds);

void DumpProcedures(AppState *state);
