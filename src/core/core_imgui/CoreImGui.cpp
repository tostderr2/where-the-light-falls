#include "CoreImGui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <GLFW/glfw3.h>

#include "CoreImGui.h"
#include "core/Log.h"

namespace Core {
namespace Gui {

static GLFWwindow *s_window = nullptr;
static bool s_uiVisible = true;

void startFrame(GLFWwindow *);
void draw();
void endFrame();

void Init(GLFWwindow *window) {
    s_window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    // NOTE: copied from opengl3 example in imgui/examples
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    style.ScaleAllSizes(scale);

    CORE_ASSERT(ImGui_ImplGlfw_InitForOpenGL(window, true), "ImGui Glfw Init for OpenGl failed!");
    const char *glsl_version = "#version 410";
    CORE_ASSERT(ImGui_ImplOpenGL3_Init(glsl_version), "ImGui Glfw Init for OpenGl failed!");

    LOG_CORE_INFO("ImGui initialised");
}

void OnUpdate(float) {
    if (!s_uiVisible)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Passthru central node = 3D scene shows through the dockspace background
    // TODO: passing 0 as an id, idk what to pass yet
    ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

    // ---  debug/HUD windows here ---
    static bool show_demo = true;
    if (show_demo)
        ImGui::ShowDemoWindow(&show_demo);

    ImGui::Render();
}
void OnRender() {
    if (!s_uiVisible)
        return;

    // Render ImGui draw data to the main framebuffer
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Render popped-out platform windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }
}

void ToggleUI() {
    s_uiVisible = !s_uiVisible;
}
bool IsUIVisible() {
    return s_uiVisible;
}

void Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
} // namespace Gui
} // namespace Core
