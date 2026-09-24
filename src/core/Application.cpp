#include "Application.h"

#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_int2.hpp>

#include "Log.h"
#include "Window.h"
#include "core_imgui/CoreImGui.h"
#include "game/Game.h"
#include "render/opengl/GLRenderDevice.h"

namespace core {

Application::Application() {
    // TODO: change this to higher number one's tested by hiting all buttons and mouse
    // reserving a block of memory for events
    m_eventBuff.events.reserve(68);
}

Application::~Application() {
    // window::Destroy(&m_window);
}

void Application::Init() {

    window::Create(&m_window, 1080, 720, "Where the light falls", &m_eventBuff);
    window::SetCallbacks(&m_window, &m_eventBuff);
    LOG_CORE_INFO("Created window");

    imgui::ImguiInit(m_window.glfwWindow);
}
Window *Application::GetWindow() {
    return &m_window;
}

void Application::ProcessEvents() {
    for (auto &event : m_eventBuff.events) {

        LOG_CORE_DEBUG("Ping window close. handled is {}", event.handled);
        // gui
        // TODO: implement on event for imgui
        // instead of letting imgui handle its own events
        // imgui::OnEvent(event);
        if (event.handled)
            continue;

        // engine
        switch (event.type) {
        case EventType::WindowClose:
            m_running = false;
            event.handled = true;
            break;
        default:
            break;
        }
        if (event.handled)
            continue;

        render::OnEvent(m_renderer, event);
        game::OnEvent(m_game, event);
    }

    eventbuffer::Clear(&m_eventBuff);
}

void Application::Run() {
    // TODO: remove the filler dt and write a simple impl
    float lastCheckedTime = glfwGetTime();

    while (m_running) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastCheckedTime;
        lastCheckedTime = currentTime;

        window::PollEvents();
        ProcessEvents();

        imgui::ImguiStartFrame();
        imgui::ImguiDraw();
        // // update state
        // game::OnUpdate(deltaTime, m_game);
        // // render
        // game::OnRender(m_game);

        imgui::ImguiEndFrame();

        window::SwapBuffers(&m_window);
    }

    imgui::ImguiShutdown();
    window::Destroy(&m_window);
}
} // namespace core
