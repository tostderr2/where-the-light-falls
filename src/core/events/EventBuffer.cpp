#include "EventBuffer.h"

#include "core/Log.h"

namespace Core {

void eventbuffer::Push(EventBuffer *buff, const Event &e) {
    // TODO: remove this after testing: how many events can happen at once
    size_t size = buff->events.size();
    size_t cap = buff->events.capacity();
    if (size == cap) {
        LOG_CORE_CRITICAL("event buffer size exceeded capacity.\n capacity: {}, size: {}", cap,
                          size);
        LOG_CORE_CRITICAL("Quitting the application: increase the capacity a bit");
        exit(-1);
    }

    buff->events.push_back(e);
}
void eventbuffer::Clear(EventBuffer *buff) {
    buff->events.clear();
}
} // namespace core
