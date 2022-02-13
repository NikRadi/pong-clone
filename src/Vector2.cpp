#include "Vector2.hpp"


Vector2
operator+(Vector2 a, Vector2 b) {
    return { a.x + b.x, a.y + b.y };
}

Vector2
operator+=(Vector2 &a, Vector2 b) {
    a = a + b;
    return a;
}

Vector2
operator-(Vector2 a) {
    return { -a.x, a.y };
}

Vector2
operator*(Vector2 a, f32 b) {
    return { a.x * b, a.y * b};
}

