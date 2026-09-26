#include "Window.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Log.h"
#include "events/Event.h"
#include "events/EventBuffer.h"

namespace Core {

namespace WindowManager {

void printPlatform(int platformId);
void glfwErrorCallback(int error, const char *description);
void setGlfwCallbacks(Window *win);

bool Create(Window *win, int width, int height, const char *title, EventBuffer *eventBuffer,
            int enableVSync) {

    // glfw init
    glfwSetErrorCallback(glfwErrorCallback);

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

    // NOTE: copied from imgui examples for opengl3
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(
        glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    win->glfwWindow =
        glfwCreateWindow((int)(main_scale * width), (int)(main_scale * height), title, NULL, NULL);
    if (win->glfwWindow == NULL) {
        LOG_CORE_CRITICAL("glfw window creation failed.");
        Destroy(win);
        return false;
    }
    LOG_CORE_INFO("created glfw window");
    // win->title = title;
    // win->height = height;
    // win->width = width;
    // win->VSync = false;
    // win->shouldClose = false;

    glfwMakeContextCurrent(win->glfwWindow);
    win->VSyncEnabled = enableVSync;
    glfwSwapInterval(enableVSync);
    LOG_CORE_INFO("VSync is enabled");

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_CORE_CRITICAL("failed to initialse GLAD");
    }
    // init glad end
    glViewport(0, 0, width, height);

    // create callback for all events

    SetCallbacks(win, eventBuffer);
    return true;
}

void SetCallbacks(Window *window, EventBuffer *eventBuffer) {
    glfwSetWindowUserPointer(window->glfwWindow, eventBuffer);
    setGlfwCallbacks(window);
}

void Destroy(Window *win) {
    if (win->glfwWindow) {
        glfwDestroyWindow(win->glfwWindow);
        LOG_CORE_INFO("destroyed window");
    }

    glfwTerminate();
    LOG_CORE_INFO("terminated glfw");
}
void ClearScreen() {
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w,
                 clearColor.z * clearColor.w, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PollEvents() {
    glfwPollEvents();
}

void SwapBuffers(Window *win) {
    glfwSwapBuffers(win->glfwWindow);
}

// utility

// all the callback funcitons and setup for glfw
void glfwErrorCallback(int error, const char *description) {
    LOG_CORE_CRITICAL("GLFW Error ({0}): {1}", error, description);
}

void windowFocusCallbackFn(GLFWwindow *window, int focused) {
    const char *msg = (focused) ? "has gained" : "has lost";
    LOG_CORE_TRACE("Window {} focus", msg);
    // TODO: set bool windowInFocus to true. not sure where we should put it rn
    // game needs to have access to it

    Event e;
    e.type = (focused) ? EventType::WindowInFocus : EventType::WindowOutOfFocus;

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void keyCallbackFn(GLFWwindow *window, int key, int , int action, int mods) {
    Event e;
    if (action == GLFW_RELEASE) {
        e.type = EventType::KeyReleased;
        e.key = {key, mods, false};
    } else {
        e.type = EventType::KeyPressed;
        e.key = {key, mods, action == GLFW_REPEAT};
    }

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void mouseButtonCallbackFn(GLFWwindow *window, int button, int action, int mods) {
    Event e;
    if (action == GLFW_PRESS) {
        e.type = EventType::MouseButtonPressed;
    } else if (action == GLFW_RELEASE) {
        e.type = EventType::MouseButtonReleased;
    }
    e.mouseButton = {button, mods};

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void mouseCursorPosCallbackFn(GLFWwindow *window, double xpos, double ypos) {
    Event e;
    e.type = EventType::MouseMoved;
    e.mouseMove = {xpos, ypos};

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void mouseScrollCallbackFn(GLFWwindow *window, double xoffset, double yoffset) {
    Event e;
    e.type = EventType::MouseScrolled;
    e.mouseScroll = {xoffset, yoffset};

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void windowSizeCallbackFn(GLFWwindow *window, int width, int height) {
    Event e;
    e.type = EventType::WindowResize;
    e.windowResize = {width, height};

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
    LOG_CORE_INFO("window resize: ({}, {})", width, height);
}

void frameBufferSizeCallbackFn(GLFWwindow *window, int width, int height) {
    // NOTE: doing this right here because in windows and mac resizing via mouse
    // stalls other events thus freezing the whole window
    // doing this here adjusts the viewport but
    // to actually smoothly render while resizing will need a micro render
    // commands at resizing phase. which is actually not even needed i guess
    // window resizing manually shouldnt be allowed in game, simple
    glViewport(0, 0, width, height);

    //  camera, ui, and custom framebuffers will need to know the changes
    //  to update on the next game tick
    Event e;
    e.type = EventType::FrameBufferResize;
    e.frameBufferResize = {width, height};

    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void windowCloseCallbackFn(GLFWwindow *window) {
    Event e;
    e.type = EventType::WindowClose;
    auto *eb = (EventBuffer *)glfwGetWindowUserPointer(window);
    eventbuffer::Push(eb, e);
}

void setGlfwCallbacks(Window *win) {

    GLFWwindow *window = win->glfwWindow;

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallbackFn);
    glfwSetWindowSizeCallback(window, windowSizeCallbackFn);
    glfwSetWindowFocusCallback(window, windowFocusCallbackFn);
    glfwSetWindowCloseCallback(window, windowCloseCallbackFn);

    glfwSetKeyCallback(window, keyCallbackFn);

    glfwSetMouseButtonCallback(window, mouseButtonCallbackFn);
    glfwSetCursorPosCallback(window, mouseCursorPosCallbackFn);
    glfwSetScrollCallback(window, mouseScrollCallbackFn);
}

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
// this feels dumb. app can just do win->height and stuff lol
int GetHeight(Window *win) {
    int wd, ht;
    glfwGetWindowSize(win->glfwWindow, &wd, &ht);
    return ht;
}
int GetWidth(Window *win) {
    int wd, ht;
    glfwGetWindowSize(win->glfwWindow, &wd, &ht);
    return wd;
}
bool GetVSync(Window *win) {
    return win->VSyncEnabled;
}
const char *GetTitle(Window *win) {
    return glfwGetWindowTitle(win->glfwWindow);
}

void GetSize(Window *win, int *width, int *height) {
    glfwGetWindowSize(win->glfwWindow, width, height);
}

GLFWwindow *GetNativeWindow(Window *win) {
    return win->glfwWindow;
}

} // namespace WindowManager

} // namespace Core
