#include "Platform.hpp"


void
UpdateButtonState(Input *input, bool is_key_down, s32 button) {
    input->buttons[button].is_changed = is_key_down != input->buttons[button].is_down;
    input->buttons[button].is_down = is_key_down;
}

bool
IsButtonDown(Input input, s32 button) {
    return input.buttons[button].is_down;
}

