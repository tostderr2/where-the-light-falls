#pragma once

#include "pch.h"

namespace Core {

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

	INVALID,
};

struct Event {
    EventType type = EventType::INVALID;
	// TODO: use this after cehcking 
	bool handled = false;
 union {
        struct { int32_t width, height; }        windowResize;
        struct { int32_t width, height; }        frameBufferResize;
        struct { int32_t keycode, mods; bool repeat; }  key;
        struct { double x, y; }               mouseMove;
        struct { int32_t button, mods; }                mouseButton;
        struct { double xOffset, yOffset; }   mouseScroll;
    };
};
} // namespace core
