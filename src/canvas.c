#include "canvas.h"
#include "renderer.h"
#include "raylib.h"
#include "util.h"
#include "vendor/HandmadeMath.h"
#include <math.h>
#include <stdio.h>

HMM_Vec2 CanvasSpaceToScreenSpace(CState *state, Canvas *canvas, HMM_Vec2 vec);

void CanvasUpdate(CState *state, Canvas *canvas) {
	canvas->screen_bounds.ZW.X += sin(GetTime());
	canvas->screen_bounds.XY.X -= sin(GetTime());
}

void CanvasRender(CState *state, Canvas *canvas) {
    CDrawRectangleLines(state, canvas->screen_bounds, BLACK);

	HMM_Vec4 bounds;
	bounds.XY = CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){0 + 10*sin(GetTime()), 0});
	bounds.ZW = CanvasSpaceToScreenSpace(state, canvas, (HMM_Vec2){50, 50});

	CDrawRectangle(state, bounds, BLACK);
}

HMM_Vec2 CanvasSpaceToScreenSpace(CState *state, Canvas *canvas, HMM_Vec2 vec) {
	HMM_Vec2 canvas_screen_size = {canvas->screen_bounds.ZW.X - canvas->screen_bounds.XY.X, 
		canvas->screen_bounds.ZW.Y - canvas->screen_bounds.XY.Y};

	HMM_Mat2 scale = {{{canvas_screen_size.Width / canvas->canvas_size.Width, 0}, {0, canvas_screen_size.Height / canvas->canvas_size.Height}}};

	HMM_Vec2 from_center = HMM_MulM2V2(scale, HMM_SubV2(vec, canvas->center));

	PrintVec2(vec);
	PrintVec2(from_center);

	return HMM_AddV2(HMM_DivV2F(HMM_AddV2(canvas->screen_bounds.XY, canvas->screen_bounds.ZW), 
				2), from_center);
}
