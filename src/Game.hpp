#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP
#include "Platform.hpp"


void InitGame();

void UpdateGame(Input input, f32 delta_time);

void RenderGame(Buffer buffer);

#endif // PONG_GAME_HPP

