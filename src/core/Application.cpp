#include "Application.h"

#include "Log.h"
#include "Window.h"

namespace core {

Application::Application() {
    // TODO: change this to higher number one's tested by hiting all buttons and mouse
	// reserving a block of memory for events
    m_eventBuff.events.reserve(10);
}

Application::~Application() {
    // window::Destroy(&m_window);
}

void Application::Init()
{

    window::Create(&m_window, 1080, 720, "Where the light falls", &m_eventBuff);
    window::SetCallbacks(&m_window, &m_eventBuff);
    LOG_CORE_INFO("Created window");
}

void Application::Run() {

    while (m_running) {
        window::PollEvents();
        if (window::ShouldClose(&m_window)) {
            m_running = false;
        }

        // update state
        // render

        window::SwapBuffers(&m_window);
        eventbuffer::Clear(&m_eventBuff);
    }

    window::Destroy(&m_window);
}

} // namespace core
