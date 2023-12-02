#include "canvas.h"
#include "raylib.h"

void CanvasUpdate(CState *state, Canvas *canvas) {}

void CanvasRender(CState *state, Canvas *canvas) {
    CDrawRectangleLines(state, canvas->screen_bounds, BLACK);
}

