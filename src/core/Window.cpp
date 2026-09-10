#include "Window.h"

#include <GLFW/glfw3.h>

#include "Log.h"

namespace core {

namespace window {

bool Create(Window *win, int width, int height, const char *title) {
    win->title = title;
    win->height = height;
    win->width = width;
    win->VSync = false;
    win->shouldClose = false;

    win->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!glfwInit()) {
        // TODO: use glfw's error that they put into some char buffer to show the error
        LOG_CORE_CRITICAL("glfw Init() failed.");
    }
    // init glad
    //
    // create callback for window events
    return true;
}
void Destroy(Window *win) {
    glfwDestroyWindow(win->window);
}
void PollEvents(Window *win) {
    glfwPollEvents();
}
bool ShouldClose(Window *win) {
    return glfwWindowShouldClose(win->window);
}
void SwapBuffers(Window *win) {
    glfwSwapBuffers(win->window);
}

int GetHeight(Window *win) {
    return win->height;
}
int GetWidth(Window *win) {
    return win->width;
}
bool GetVSync(Window *win) {
    return win->VSync;
}
const char *GetTitle(Window *win) {
    return win->title;
}

} // namespace window

// std::unique_ptr<Window> Window::Create(const WindowProps &props) {
//     // make a constructor
//     //
//     std::unique_ptr<Window> window = std::make_unique<Window>();
//
//     return *this;
// }
//
// Window::Window(WindowProps &props) {
//     m_data.Title = props.Title;
//     m_data.Width = props.Width;
//     m_data.Height = props.Height;
//     m_data.VSync = props.VSync;
// }
//
// GLFWwindow *Window::GetWindowPtr() {
//     // raw ptr is good/bad/ok ???
//     return m_window;
// }
// int Window::GetHeight() {
//     return m_data.Height;
// }
// int Window::GetWidth() {
//     return m_data.Width;
// }
// bool Window::GetVsync() {
//     return m_data.VSync;
// }

// pods style

} // namespace core
