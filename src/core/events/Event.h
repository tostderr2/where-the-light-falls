#pragma once

#include "pch.h"

namespace core {

enum class EventType : uint8_t {
    WindowResize,
    WindowClose,
    WindowInFocus,
	WindowOutOfFocus,

    KeyPressed,
    KeyReleased,

    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScrolled,

	FrameBufferResize,
};

struct Event {
    EventType type;
 union {
        struct { int width, height; }        windowResize;
        struct { int width, height; }        frameBufferResize;
        struct { int keycode; bool repeat; }  key;
        struct { double x, y; }               mouseMove;
        struct { int button; }                mouseButton;
        struct { double xOffset, yOffset; }   mouseScroll;
    };
};
} // namespace core
