#include <Windows.h>
#include "Common.hpp"
#include "Game.hpp"
#include "Platform.hpp"
#include "MainWin32.hpp"


static bool is_window_open = true;
static Win32Buffer win32buffer;


static void
Win32ProcessMessages(Input *input) {
    MSG message = {};
    while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
        switch (message.message) {
            case WM_KEYDOWN:
            case WM_KEYUP: {
                bool is_key_down = (message.lParam & (1 << 31)) == 0;
                u32 vk_code = static_cast<u32>(message.wParam);
                switch (vk_code) {
                    case 'S': { UpdateButtonState(input, is_key_down, BUTTON_S); } break;
                    case 'W': { UpdateButtonState(input, is_key_down, BUTTON_W); } break;
                    case VK_ESCAPE: {
                        is_window_open = false;
                    } break;
                }
            } break;
            default: {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            } break;
        }
    }
}

LRESULT CALLBACK
Win32WindowCallback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    LRESULT result = 0;
    switch (message) {
        case WM_SIZE: {
            RECT rect;
            GetClientRect(window, &rect);
            win32buffer.width = rect.right - rect.left;
            win32buffer.height = rect.bottom - rect.top;

            if (win32buffer.memory) {
                VirtualFree(win32buffer.memory, 0, MEM_RELEASE);
            }

            s32 size = win32buffer.width * win32buffer.height * sizeof(s32);
            win32buffer.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            win32buffer.info.bmiHeader.biSize = sizeof(win32buffer.info.bmiHeader);
            win32buffer.info.bmiHeader.biWidth = win32buffer.width;
            win32buffer.info.bmiHeader.biHeight = win32buffer.height;
            win32buffer.info.bmiHeader.biPlanes = 1;
            win32buffer.info.bmiHeader.biBitCount = 32;
            win32buffer.info.bmiHeader.biCompression = BI_RGB;
        } break;
        case WM_CLOSE:
        case WM_DESTROY: {
            is_window_open = false;
        } break;
        default: {
            result = DefWindowProc(window, message, w_param, l_param);
        } break;
    }

    return result;
}

s32
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, s32 show_code) {
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = Win32WindowCallback;
    window_class.hInstance = instance;
    window_class.lpszClassName = "PongWindowClass";
    RegisterClass(&window_class);

    HWND window = CreateWindowEx(
        0,              // Specifies the extended style of the window
        window_class.lpszClassName,
        "Pong",         // Window name
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,  // Horizontal position of the window
        CW_USEDEFAULT,  // Vertical position of the window
        CW_USEDEFAULT,  // Window width
        CW_USEDEFAULT,  // Window height
        0,              // Handle to parent or owner window
        0,              // Handle to window menu
        instance,
        0               // Pointer to a value to be passed to the window
    );

    InitGame();
    Input input = {};
    HDC device_context = GetDC(window);
    f32 delta_time = 0.0166f;

    LARGE_INTEGER pf;
    QueryPerformanceFrequency(&pf);
    s64 performance_frequency = pf.QuadPart;

    LARGE_INTEGER frame_time_begin;
    QueryPerformanceCounter(&frame_time_begin);
    while (is_window_open) {
        for (s32 i = 0; i < BUTTON_COUNT; ++i) {
            input.buttons[i].is_changed = false;
        }

        Win32ProcessMessages(&input);
        UpdateGame(input, delta_time);

        Buffer buffer = {};
        buffer.memory = win32buffer.memory;
        buffer.width = win32buffer.width;
        buffer.height = win32buffer.height;
        RenderGame(buffer);

        StretchDIBits(
            device_context,
            0, 0, win32buffer.width, win32buffer.height,
            0, 0, win32buffer.width, win32buffer.height,
            win32buffer.memory, &win32buffer.info,
            DIB_RGB_COLORS,
            SRCCOPY
        );

        LARGE_INTEGER frame_time_end;
        QueryPerformanceCounter(&frame_time_end);
        delta_time = static_cast<f32>(frame_time_end.QuadPart - frame_time_begin.QuadPart) / performance_frequency;
        frame_time_begin = frame_time_end;
    }

    ReleaseDC(window, device_context);
    return 0;
}

