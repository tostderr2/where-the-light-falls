#pragma once

#include <imgui_impl_glfw.h>

namespace Core {
namespace Gui {

void Init(GLFWwindow *);
void OnUpdate(float deltaTime);
void OnRender();
void Shutdown();

} // namespace Gui
} // namespace Core
