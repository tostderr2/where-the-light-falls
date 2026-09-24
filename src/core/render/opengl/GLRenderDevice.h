#pragma once

// #if defined(USE_OPENGL)
#include "core/events/Event.h"
namespace core {

namespace render {
struct Renderer {};

void OnEvent(Renderer &, Event &);
} // namespace render
} // namespace core
// #endif
