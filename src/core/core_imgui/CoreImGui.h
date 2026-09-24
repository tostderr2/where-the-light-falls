#pragma once

#include <imgui_impl_glfw.h>

namespace core {
namespace imgui {

void ImguiInit(GLFWwindow *window);
void ImguiStartFrame();
void ImguiDraw();
void ImguiEndFrame(/*GLFWwindow *window */);
void ImguiShutdown();

} // namespace imgui
} // namespace core
