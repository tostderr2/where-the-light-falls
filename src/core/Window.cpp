#include "Window.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Log.h"

namespace core {

namespace window {
// utility
void printPlatform(int platformId);
void glfw_error_callback(int error, const char *description);

void framebufferSizeCallback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}
bool Create(Window *win, int width, int height, const char *title) {

    // glfw init
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        // TODO: use glfw's error that they put into some char buffer to show the error
        LOG_CORE_CRITICAL("glfw Init() failed. ");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    int platform = glfwGetPlatform();
    printPlatform(platform);
    // glfw init end

    win->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (win->window == NULL) {
        LOG_CORE_CRITICAL("glfw window creation failed.");
        Destroy(win);
        return false;
    }
    LOG_CORE_INFO("created glfw window");
    win->title = title;
    win->height = height;
    win->width = width;
    win->VSync = false;
    win->shouldClose = false;

    glfwMakeContextCurrent(win->window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_CORE_CRITICAL("failed to initialse GLAD");
    }
    // init glad end

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(win->window, framebufferSizeCallback);

    // create callback for all events
    return true;
}
void Destroy(Window *win) {
    if (win->window) {
        glfwDestroyWindow(win->window);
        LOG_CORE_INFO("destroyed window");
    }

    glfwTerminate();
    LOG_CORE_INFO("terminated glfw");
}
void PollEvents() {
    glfwPollEvents();
}
bool ShouldClose(Window *win) {
    return glfwWindowShouldClose(win->window);
}
void SwapBuffers(Window *win) {
    glfwSwapBuffers(win->window);
}

// utility
void printPlatform(int platformId) {
    const char *platform;
    switch (platformId) {
    case GLFW_ANY_PLATFORM: {
        platform = "ANY";
        break;
    }
    case GLFW_PLATFORM_WIN32: {
        platform = "WIN32";
        break;
    }
    case GLFW_PLATFORM_COCOA: {
        platform = "COCOA";
        break;
    }
    case GLFW_PLATFORM_WAYLAND: {
        platform = "WAYLAND";
        break;
    }
    case GLFW_PLATFORM_X11: {
        platform = "X11";
        break;
    }
    case GLFW_PLATFORM_NULL: {
        platform = "NULL";
        break;
    }
    }
    LOG_CORE_INFO("glfw initiated for platform: {}", platform);
}

void glfw_error_callback(int error, const char *description) {
    LOG_CORE_CRITICAL("GLFW Error ({0}): {1}", error, description);
}

// this feels dumb. app can just do win->height and stuff lol
// int GetHeight(Window *win) {
//     return win->height;
// }
// int GetWidth(Window *win) {
//     return win->width;
// }
// bool GetVSync(Window *win) {
//     return win->VSync;
// }
// const char *GetTitle(Window *win) {
//     return win->title;
// }

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
