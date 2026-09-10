#pragma once

#include <imgui_impl_glfw.h>

#include "common.h"

namespace core {

struct Window {
    GLFWwindow *window = nullptr;

    // data
    const char *title = "where the light falls";
    int height = 0;
    int width = 0;
    bool VSync = false;
    bool shouldClose = false;
};

namespace window {

bool Create(Window *win, int width, int height, const char *title);
void Destroy(Window *window);
void PollEvents(Window *window);
bool ShouldClose(Window *window);
void SwapBuffers(Window *window);

int GetHeight(Window *win);
int GetWidth(Window *win);
bool GetVSync(Window *win);
const char *GetTitle(Window *win);
} // namespace window

// struct WindowProps {
//     std::string Title = "Where the light falls";
//     int Width = 1080;
//     int Height = 720;
//     bool VSync = false;
// };
//
// class Window {
//     // has to switch between opengl and vulkan(not gonna use this, but to be able to reuse thing
//     // engine part else where would be good to have)
//     // later we can add a build option -DGRAPHICS_API=Vulkan or opengl. rn not gonna bother
//
//   public:
//     // to be able to give back a ptr to window itself
//     static std::unique_ptr<Window> Create(const WindowProps &props = WindowProps());
//
//     void OnUpdate();
//
//     GLFWwindow *GetWindowPtr();
//     int GetHeight();
//     int GetWidth();
//     bool GetVsync();
//
//   private:
//     explicit Window(WindowProps &props);
//
//     struct WindowData {
//         std::string Title;
//         int Width;
//         int Height;
//         bool VSync;
//     };
//
//     GLFWwindow *m_window = nullptr;
//     WindowData m_data;
// };

} // namespace core
