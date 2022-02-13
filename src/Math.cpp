#include "Math.hpp"


s32
Clamp(s32 value, s32 min, s32 max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

