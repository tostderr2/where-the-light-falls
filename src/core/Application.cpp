#include "Application.h"
#include "core/Window.h"

namespace core {

Application::Application() {
	window::Create(&m_window, 1080, 720, "Where the light falls");



}
Application::~Application()
{
	window::Destroy(&m_window);
}
void Application::Run() {

    while (m_running) {
        // profiler start

        // input update
        // window update
        // render window

        // profiler end
    }
}

} // namespace core
