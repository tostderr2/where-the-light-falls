#include "Application.h"

#include <imgui.h>

#include "Log.h"
#include "Window.h"
#include "core/Input.h"
#include "core/events/Event.h"
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

    Core::Log::Shutdown();
}

void Application::Init() {

    Core::Log::Init();

    // init window and eventBuffer
    m_running = true;
    WindowManager::Create(&m_window, 1080, 720, "Where the light falls", &m_eventBuff);
    LOG_CORE_INFO("Created window");

    // InputManager::Init(m_inputState);
    LOG_CORE_INFO("input state initiated");

    Gui::Init(m_window.glfwWindow);
    m_running = true;
    // TODO: init m_game and m_renderer
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

        InputManager::Update(m_inputState, m_window.glfwWindow);

        processEvents();
        updateStates(deltaTime);
        render();

        WindowManager::SwapBuffers(&m_window);
    }
}

Window *Application::GetWindow() {
    return &m_window;
}

inline bool IsMouseEvent(Event &e) {
    // TODO: make a bit mask for different event
    return (e.type == EventType::MouseButtonPressed || e.type == EventType::MouseButtonReleased ||
            e.type == EventType::MouseMoved || e.type == EventType::MouseScrolled);
}

inline bool IsKeyboardEvent(Event &e) {
    return (e.type == EventType::KeyPressed || e.type == EventType::KeyReleased);
}

void Application::processEvents() {
    for (auto &event : m_eventBuff.events) {

        // engine
        switch (event.type) {
        case EventType::WindowClose:
            m_running = false;
            event.handled = true;
            break;
        case EventType::FrameBufferResize:
            WindowManager::UpdateForFrameBufferChange(&m_window);
            break;

            // input events
        case EventType::KeyPressed:
            InputManager::OnKeyPressed(m_inputState, event.key.keycode);
            event.handled = true;
            break;
        case EventType::KeyReleased:
            InputManager::OnKeyReleased(m_inputState, event.key.keycode);
            event.handled = true;
            break;

        case EventType::MouseButtonPressed:
            InputManager::OnMouseButtonPressed(m_inputState, event.key.keycode);
            event.handled = true;
            break;
        case EventType::MouseButtonReleased:
            InputManager::OnMouseButtonReleased(m_inputState, event.key.keycode);
            event.handled = true;
            break;

        case EventType::MouseMoved:
            InputManager::OnMouseMoved(m_inputState, event.mouseMove.x, event.mouseMove.y);
            event.handled = true;
            break;

        case EventType::MouseScrolled:
            InputManager::OnMouseScrolled(m_inputState, event.mouseScroll.xOffset,
                                          event.mouseScroll.yOffset);
            event.handled = true;
            break;

        default:
            break;
        }
        if (event.handled)
            continue;

        // gui
        // skip if the imgui is using the events
        // TODO: skip the mouse movement when imgui is visible
        // check is imgui visible, and then we need to spawn the mouse
        // and disble mouse player movements
        ImGuiIO &io = ImGui::GetIO();
        if (IsMouseEvent(event) && io.WantCaptureMouse) {
            continue;
        }
        if (IsKeyboardEvent(event) && io.WantCaptureKeyboard | io.WantTextInput)
            continue;

        // game
        // immidiate, fire once events like jumping and hitting
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
