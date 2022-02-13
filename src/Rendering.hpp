#ifndef PONG_RENDERING_HPP
#define PONG_RENDERING_HPP
#include "Common.hpp"
#include "Platform.hpp"


void
DrawRectInPixels(Buffer buffer, s32 x0, s32 y0, s32 x1, s32 y1, u32 color);

void
DrawRect(Buffer buffer, f32 x, f32 y, f32 half_width, f32 half_height, u32 color);

#endif // PONG_RENDERING_HPP

