#pragma once
#include <GLFW/glfw3.h>

namespace Core {
namespace Gui {

void Init(GLFWwindow *window);
void OnUpdate(float dt);
void OnRender();
void ToggleUI();
bool IsUIVisible();
void Shutdown();

} // namespace Gui
} // namespace Core
