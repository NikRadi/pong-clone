#ifndef PONG_MAIN_WIN32_HPP
#define PONG_MAIN_WIN32_HPP


struct Win32Buffer {
    s32 width;
    s32 height;
    void *memory;
    BITMAPINFO info;
};

#endif // PONG_MAIN_WIN32_HPP

