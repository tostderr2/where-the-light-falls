#pragma once

#include <imgui_impl_glfw.h>

#include "events/EventBuffer.h"

namespace core {

// TODO:
// as i will only be using opengl in this game
// this struct is not necessary
// can make a helper function on glfw's layer for these simple
// data
struct Window {
    GLFWwindow *window = nullptr;

     bool VSyncEnabled = false;
    // // data
    // const char *title = "where the light falls";
    // int height = 0;
    // int width = 0;
    // bool shouldClose = false;
};

namespace window {

bool Create(Window *, int, int, const char *, EventBuffer *,int enableVSync = 0);
void Destroy(Window *);
void PollEvents();
bool ShouldClose(Window *);
void SwapBuffers(Window *);
void SetCallbacks(Window *, EventBuffer *);
// int GetHeight(Window *win);
// int GetWidth(Window *win);
// bool GetVSync(Window *win);
// const char *GetTitle(Window *win);
} // namespace window

} // namespace core
