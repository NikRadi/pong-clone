#include "Rendering.hpp"
#include "Platform.hpp"
#include "Math.hpp"


void
DrawRectInPixels(Buffer buffer, s32 x0, s32 y0, s32 x1, s32 y1, u32 color) {
    x0 = Clamp(x0, 0, buffer.width);
    y0 = Clamp(y0, 0, buffer.height);
    x1 = Clamp(x1, 0, buffer.width);
    y1 = Clamp(y1, 0, buffer.height);
    for (int y = y0; y < y1; ++y) {
        u32 *pixel = static_cast<u32 *>(buffer.memory) + x0 + y * buffer.width;
        for (int x = x0; x < x1; ++x) {
            *pixel = color;
            pixel += 1;
        }
    }
}

void
DrawRect(Buffer buffer, f32 x, f32 y, f32 half_width, f32 half_height, u32 color) {
    x *= buffer.height * RENDER_SCALE;
    y *= buffer.height * RENDER_SCALE;
    half_width *= buffer.height * RENDER_SCALE;
    half_height *= buffer.height * RENDER_SCALE;

    x += buffer.width / 2.0f;
    y += buffer.height / 2.0f;

    // Convert to pixels
    s32 x0 = static_cast<s32>(x - half_width);
    s32 y0 = static_cast<s32>(y - half_height);
    s32 x1 = static_cast<s32>(x + half_width);
    s32 y1 = static_cast<s32>(y + half_height);
    DrawRectInPixels(buffer, x0, y0, x1, y1, color);
}

