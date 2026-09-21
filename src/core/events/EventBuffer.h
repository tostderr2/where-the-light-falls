#pragma once

#include <vector>

#include "Event.h"

namespace core {

struct EventBuffer {
    std::vector<Event> events;
};

namespace eventbuffer {
void Push(EventBuffer *, const Event &);
void Clear(EventBuffer *);
} // namespace eventbuffer

} // namespace core
