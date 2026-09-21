#pragma once

#include "Core.h"
#include "Window.h"
#include "events/EventBuffer.h"

namespace core {

class CORE_API Application {
  public:
    Application();
    ~Application();

    void Run();
    void Init();

  private:
    Window m_window;

    EventBuffer m_eventBuff;
    bool m_running;
};

} // namespace core
