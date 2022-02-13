#include "Game.hpp"
#include "Rendering.hpp"


void InitGame() {
}

void UpdateGame(Input input, f32 delta_time) {
}

void RenderGame(Buffer buffer) {
    DrawRectInPixels(buffer, 10, 10, 50, 50, 0xffff00);
    DrawRect(buffer, 0.2f, 0.2f, 0.5f, 0.5f, 0x00ffff);
}

