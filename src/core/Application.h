#pragma once

#include <imgui.h>

#include "Core.h"
#include "Window.h"
#include "events/EventBuffer.h"
#include "game/Game.h"

namespace core {

class CORE_API Application {
  public:
    Application();
    ~Application();

    void Run();
    void Init();
    Window *GetWindow();

  private:
    Window m_window;

    EventBuffer m_eventBuff;
    bool m_running;
    // game::Game* m_game;
};

} // namespace core
