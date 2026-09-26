#pragma once

#include <imgui.h>

#include "Core.h"
#include "Window.h"
#include "core/render/opengl/GLRenderDevice.h"
#include "events/EventBuffer.h"
#include "game/Game.h"

namespace Core {

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
	InGame::Game m_game;
    Renderer::Renderer m_renderer;

  private:
    void processEvents();
    void updateStates(float);
    void render();
};

} // namespace core
