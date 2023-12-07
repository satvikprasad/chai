#include "defines.h"
#include "vendor/HandmadeMath.h"
#include <stdio.h>

void PrintVec2(HMM_Vec2 vec) { printf("(%f, %f)\n", vec.X, vec.Y); }

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
