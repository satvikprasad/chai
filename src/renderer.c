#include "renderer.h"
#include "cstate.h"
#include "raylib.h"
#include "vendor/HandmadeMath.h"

void CDrawRectangle(CState *state, HMM_Vec4 bounds, Color color) {
	if (HMM_EqV2(bounds.XY, bounds.ZW)) return;

	DrawRectangleRec((Rectangle){bounds.XY.X, state->window_size.Y - bounds.ZW.Y,
			bounds.ZW.X - bounds.XY.X, bounds.ZW.Y - bounds.XY.Y},
			BLACK);
}

void CDrawLine(CState *state, HMM_Vec2 vertices[2], Color color) {
	if (HMM_EqV2(vertices[0], vertices[1])) return;

	DrawLine(vertices[0].X, state->window_size.Height - vertices[0].Y, vertices[1].X, state->window_size.Height - vertices[1].Y, color);
}

void CDrawLineInBounds(CState *state, HMM_Vec2 vertices[2], HMM_Vec4 bounds, Color color) {
#define HMEW(a, b, r) ((r) - (a).X)/((b).X - (a).X)
#define VMEW(a, b, r) ((r) - (a).Y)/((b).Y - (a).Y)
#define INTERSECT(a, b, mew) {(mew)*(b).X + (a).X*(1-(mew)), (mew)*(b).Y + (a).Y*(1-(mew))};


	f32 left_mew = HMEW(vertices[0], vertices[1], bounds.XY.X);
	HMM_Vec2 left_intersect = INTERSECT(vertices[0], vertices[1], left_mew);

	f32 right_mew = HMEW(vertices[0], vertices[1], bounds.ZW.X);
	HMM_Vec2 right_intersect = INTERSECT(vertices[0], vertices[1], right_mew);

	f32 top_mew = VMEW(vertices[0], vertices[1], bounds.ZW.Y);
	HMM_Vec2 top_intersect = INTERSECT(vertices[0], vertices[1], top_mew);

	f32 bottom_mew = VMEW(vertices[0], vertices[1], bounds.XY.Y);
	HMM_Vec2 bottom_intersect = INTERSECT(vertices[0], vertices[1], bottom_mew);

	for (u32 i = 0; i < 2; ++i) {
		if (vertices[i].X < left_intersect.X) {
			vertices[i] = left_intersect;
		}
		if (vertices[i].X > right_intersect.X) {
			vertices[i] = right_intersect;
		}
		if (vertices[i].Y < bottom_intersect.Y) {
			vertices[i] = bottom_intersect;
		}
		if (vertices[i].Y > top_intersect.Y) {
			vertices[i] = top_intersect;
		}
	}

	if (vertices[0].X == vertices[1].X) {
		if (vertices[0].X > bounds.ZW.X) {
			vertices[0].X = bounds.ZW.X;
			vertices[1].X = bounds.ZW.X;
		}

		if (vertices[0].X < bounds.XY.X) {
			vertices[0].X = bounds.XY.X;
			vertices[1].X = bounds.XY.X;
		}
	}

	if (vertices[0].Y == vertices[1].Y) {
		if (vertices[0].Y > bounds.ZW.Y) {
			vertices[0].Y = bounds.ZW.Y;
			vertices[1].Y = bounds.ZW.Y;
		}

		if (vertices[0].Y < bounds.XY.Y) {
			vertices[0].Y = bounds.XY.Y;
			vertices[1].Y = bounds.XY.Y;
		}
	}

	CDrawLine(state, vertices, color);
}

void CDrawRectangleLines(CState *state, HMM_Vec4 bounds, Color color) {
	DrawRectangleLines(bounds.XY.X, state->window_size.Y - bounds.ZW.Y, bounds.ZW.X - bounds.XY.X,
			bounds.ZW.Y - bounds.XY.Y, BLACK);
}

