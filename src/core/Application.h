#pragma once

#include "core/Core.h"
#include "core/Window.h"

namespace core {

class CORE_API Application {
public:
    Application();
    ~Application();

    void Run();

  private:
    Window m_window;

	bool m_running;
};

} // namespace core
