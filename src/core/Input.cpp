#include "Input.h"

#include <GLFW/glfw3.h>

// input api for the game side
// key inputs
bool Core::InputManager::IsKeyDown(State &state, int keycode) {
    if (keycode < 0 || keycode > GLFW_KEY_LAST)
        return false;

    return state.currentKeys[keycode];
}
bool Core::InputManager::WasKeyPressed(State &keyState, int keycode) {
    if (keycode < 0 || keycode > GLFW_KEY_LAST)
        return false;

    return keyState.currentKeys[keycode] && !keyState.previousKeys[keycode];
}
bool Core::InputManager::WasKeyReleased(State &keyState, int keycode) {
    if (keycode < 0 || keycode > GLFW_KEY_LAST)
        return false;

    return !keyState.currentKeys[keycode] && keyState.previousKeys[keycode];
}

// mouse inputs
bool Core::InputManager::IsMouseKeyDown(State &keyState, int keycode) {
    if (keycode < 0 || keycode > GLFW_MOUSE_BUTTON_LAST)
        return false;

    return keyState.currentMouseButtons[keycode];
}
bool Core::InputManager::WasMouseKeyPressed(State &keyState, int keycode) {
    if (keycode < 0 || keycode > GLFW_MOUSE_BUTTON_LAST)
        return false;

    return keyState.currentMouseButtons[keycode] && !keyState.previousMouseButtons[keycode];
}
bool Core::InputManager::WasMouseKeyReleased(State &keyState, int keycode) {
    if (keycode < 0 || keycode > GLFW_MOUSE_BUTTON_LAST)
        return false;

    return !keyState.currentMouseButtons[keycode] && keyState.previousMouseButtons[keycode];
}

double Core::InputManager::GetMousePosX(State &keyState) {
    return keyState.mouseX;
}
double Core::InputManager::GetMousePosY(State &keyState) {
    return keyState.mouseY;
}

double Core::InputManager::GetMouseDeltaX(State &keyState) {
    return keyState.mouseX - keyState.lastMouseX;
}
double Core::InputManager::GetMouseDeltaY(State &keyState) {
    return keyState.mouseY - keyState.lastMouseY;
}

double Core::InputManager::GetScrollX(State &keyState) {
    return keyState.scrollX;
}
double Core::InputManager::GetScrollY(State &keyState) {
    return keyState.scrollY;
}

void Core::InputManager::Update(State &state, GLFWwindow *) {

    for (int i = 0; i <= GLFW_KEY_LAST; ++i) {
        state.previousKeys[i] = state.currentKeys[i];
    }
    for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i) {
        state.previousMouseButtons[i] = state.currentMouseButtons[i];
    }

    state.lastMouseX = state.mouseX;
    state.lastMouseY = state.mouseY;

    state.scrollX = 0;
    state.scrollY = 0;
}

void Core::InputManager::OnKeyPressed(State &state, int keycode) {
    state.currentKeys[keycode] = true;
}

void Core::InputManager::OnKeyReleased(State &state, int keycode) {
    state.currentKeys[keycode] = false;
}

void Core::InputManager::OnMouseButtonPressed(State &state, int keycode) {
    state.currentMouseButtons[keycode] = true;
}

void Core::InputManager::OnMouseButtonReleased(State &state, int keycode) {
    state.currentMouseButtons[keycode] = false;
}

void Core::InputManager::OnMouseMoved(State &state, double xpos, double ypos) {
    if (state.firstMouseMove) {
        state.lastMouseX = xpos;
        state.lastMouseY = ypos;
        state.firstMouseMove = false;
    }
    state.mouseX = xpos;
    state.mouseY = ypos;
}

void Core::InputManager::OnMouseScrolled(State &state, double xOffset, double yOffset) {
    state.scrollX += xOffset;
    state.scrollY += yOffset;
}
