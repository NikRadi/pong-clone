#ifndef PONG_PLATFORM_HPP
#define PONG_PLATFORM_HPP
#include "Common.hpp"


enum {
    BUTTON_S,
    BUTTON_W,

    BUTTON_COUNT
};

struct ButtonState {
    bool is_down;
    bool is_changed;
};

struct Input {
    ButtonState buttons[BUTTON_COUNT];
};

struct Buffer {
    s32 width;
    s32 height;
    void *memory;
};


void
UpdateButtonState(Input *input, bool is_key_down, s32 button);

#endif // PONG_PLATFORM_HPP

