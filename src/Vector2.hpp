#ifndef PONG_VECTOR2_HPP
#define PONG_VECTOR2_HPP
#include "Common.hpp"


struct Vector2 {
    f32 x;
    f32 y;
};


Vector2
operator+(Vector2 a, Vector2 b);

Vector2
operator+=(Vector2 &a, Vector2 b);

Vector2
operator-(Vector2 a);

Vector2
operator*(Vector2 a, f32 b);

#endif // PONG_VECTOR2_HPP

