#include "Application.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_int2.hpp>

#include "Log.h"
#include "Window.h"
#include "core/time/CoreTime.h"
#include "core_imgui/CoreImGui.h"
#include "game/Game.h"

namespace Core {

Application::Application() {
    // TODO: change this to higher number one's tested by hiting all buttons and mouse
    // reserving a block of memory for events
    m_eventBuff.events.reserve(68);
}

Application::~Application() {
    Gui::Shutdown();
    WindowManager::Destroy(&m_window);
}

void Application::Init() {

    WindowManager::Create(&m_window, 1080, 720, "Where the light falls", &m_eventBuff);
    WindowManager::SetCallbacks(&m_window, &m_eventBuff);
    LOG_CORE_INFO("Created window");

    Gui::Init(m_window.glfwWindow);
}

void Application::Run() {
    // TODO: remove the filler dt and write a simple impl
    float lastCheckedTime = Time::CurrentTime();

    while (m_running) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastCheckedTime;
        lastCheckedTime = currentTime;

        WindowManager::ClearScreen();
        WindowManager::PollEvents();

        processEvents();
        updateStates(deltaTime);
        render();

        WindowManager::SwapBuffers(&m_window);
    }
}

Window *Application::GetWindow() {
    return &m_window;
}

void Application::processEvents() {
    for (auto &event : m_eventBuff.events) {
        // gui
        // TODO: implement on event for imgui
        // instead of letting imgui handle its own events
        // Gui::OnEvent(event);
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

		// immidiate, once fire events like jumping and hitting
        InGame::OnEvent(m_game, event);
    }

    eventbuffer::Clear(&m_eventBuff);
}
void Application::updateStates(float deltaTime) {
    Gui::OnUpdate(deltaTime);

    // persistance updates, updating the state of the objects
	// like moving ahead, until the key is released
    InGame::OnUpdate(deltaTime, m_game);
}

void Application::render() {
    Gui::OnRender();

    InGame::OnRender(m_game);
}

} // namespace Core
