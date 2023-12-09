#include "cstate.h"
#include "defines.h"
#include "vendor/HandmadeMath.h"
#include <stdio.h>

void PrintVec2(HMM_Vec2 vec) { printf("(%f, %f)\n", vec.X, vec.Y); }
void PrintVec3(HMM_Vec3 vec) { printf("(%f, %f, %f)\n", vec.X, vec.Y, vec.Z); }
void PrintVec4(HMM_Vec4 vec) { printf("(%f, %f, %f, %f)\n", vec.X, vec.Y, vec.Z, vec.W); }

HMM_Vec2 ClampV2ToBounds(HMM_Vec2 vec, HMM_Vec4 bounds) {
	if(vec.X <= bounds.XY.X) {
		vec.X = bounds.XY.X + 1;
	}
	if(vec.Y <= bounds.XY.Y) {
		vec.Y = bounds.XY.Y + 1;
	}
	if(vec.X >= bounds.ZW.X) {
		vec.X = bounds.ZW.X - 1;
	}
	if(vec.Y >= bounds.ZW.Y) {
		vec.Y = bounds.ZW.Y - 1;
	}

	return vec;
}

b8 V2InBounds(HMM_Vec2 vec, HMM_Vec4 bounds) {
	if(vec.X < bounds.XY.X) {
		return false;
	}
	if(vec.Y < bounds.XY.Y) {
		return false;
	}
	if(vec.X > bounds.ZW.X) {
		return false;
	}
	if(vec.Y > bounds.ZW.Y) {
		return false;
	}

	return true;
}

void DumpProcedures(CState *state) {
	for (u32 i = 0; i < state->procedure_count; ++i) {
		Procedure proc = state->procedures[i];

		printf("Procedure %u: (%s, %s)\n", i, proc.func, proc.name);
	}
}
