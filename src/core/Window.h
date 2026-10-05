#pragma once

#include <imgui_impl_glfw.h>

#include "events/EventBuffer.h"
#include "math/common.h"

namespace Core {

struct Window {
    GLFWwindow *glfwWindow = nullptr;

    bool VSyncEnabled = false;
    // // data
    // const char *title = "where the light falls";
    // int height = 0;
    // int width = 0;
    // bool shouldClose = false;
};

namespace WindowManager {

bool Create(Window *, int width, int height, const char *title, EventBuffer *, int enableVSync = 0);
void Destroy(Window *);
void ClearScreen();
void PollEvents();
void SwapBuffers(Window *);
void SetCallbacks(Window *, EventBuffer *);
void GetSize(Window *, int *width, int *height);
GLFWwindow *GetNativeWindow(Window *);
void UpdateForFrameBufferChange(Window *win);

// helpers
int GetHeight(Window *win);
int GetWidth(Window *win);
bool GetVSync(Window *win);
const char *GetTitle(Window *win);
} // namespace WindowManager

} // namespace Core
