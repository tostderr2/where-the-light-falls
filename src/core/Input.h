#pragma once

#include <GLFW/glfw3.h>

namespace Core {
namespace InputManager {

struct State {
    bool currentKeys[GLFW_KEY_LAST + 1] = {false};
    bool previousKeys[GLFW_KEY_LAST + 1] = {false};

    bool currentMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1] = {false};
    bool previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1] = {false};

    // mouse abs pos
    double mouseX = 0.0;
    double mouseY = 0.0;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool firstMouseMove = true;

    double scrollX = 0.0;
    double scrollY = 0.0;
};

bool IsKeyDown(State &keyState, int keycode);
bool WasKeyPressed(State &keyState, int keycode);
bool WasKeyReleased(State &keyState, int keycode);

bool IsMouseKeyDown(State &keyState, int keycode);
bool WasMouseKeyPressed(State &keyState, int keycode);
bool WasMouseKeyReleased(State &keyState, int keycode);
double GetMousePosX(State &keyState);
double GetMousePosY(State &keyState);
double GetMouseDeltaX(State &keyState);
double GetMouseDeltaY(State &keyState);
double GetScrollX(State &keyState);
double GetScrollY(State &keyState);

void Update(State &keyState, GLFWwindow *);

void OnKeyPressed(State &keyState, int keycode);
void OnKeyReleased(State &keyState, int keycode);

void OnMouseButtonPressed(State &keyState, int keycode);
void OnMouseButtonReleased(State &keyState, int keycode);
void OnMouseMoved(State &keyState, double xpos, double ypos);
void OnMouseScrolled(State &keyState, double xOffset, double yOffset);
} // namespace InputManager

} // namespace Core
