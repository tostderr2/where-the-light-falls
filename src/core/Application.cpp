#include "Application.h"

#include "core/Log.h"
#include "core/Window.h"

namespace core {

Application::Application() {
    window::Create(&m_window, 1080, 720, "Where the light falls");
    LOG_CORE_INFO("Created window");
}
Application::~Application() {
    window::Destroy(&m_window);
}
void Application::Run() {

    LOG_CORE_DEBUG("Entering main loop");

    while (m_running) {
        window::PollEvents();
        if (window::ShouldClose(&m_window)) {
            m_running = false;
        }

		// update state
		// render

        window::SwapBuffers(&m_window);
    }
}

} // namespace core
