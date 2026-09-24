#include "CoreImGui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <GLFW/glfw3.h>

#include "core/Log.h"

namespace core {
namespace imgui {

void ImguiInit(GLFWwindow *window) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // NOTE: have set this on a whim, not sure if any  more are required
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
    // TODO: need to switch to a different branch where they have these flags
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    // NOTE: copied from opengl3 example in imgui/examples
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(
        glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(
        main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style
                     // scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale; // Set initial font scale. (in docking branch: using
                                     // io.ConfigDpiScaleFonts=true automatically overrides this for
                                     // every window depending on the current monitor)

    CORE_ASSERT(ImGui_ImplGlfw_InitForOpenGL(window, true), "ImGui Glfw Init for OpenGl failed!");
    // NOTE: copied from opengl3 example in imgui/examples
    // TODO: check why this was written
    const char *glsl_version = "#version 410";
    CORE_ASSERT(ImGui_ImplOpenGL3_Init(glsl_version), "ImGui Glfw Init for OpenGl failed!");

    LOG_CORE_INFO("imgui initialised and started new frame");
}

void ImguiStartFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiDraw() {

    static bool show_demo_window = true;
    static bool show_another_window = false;

    ImGuiIO &io = ImGui::GetIO();
    ImGui::Begin("Debug Menu");
    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
    // io.Framerate);

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::End();

    // NOTE: copied from opengl3 example form imgui/examples
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text(
        "This is some useful text."); // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window",
                    &show_demo_window); // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color",
                      (float *)&clearColor); // Edit 3 floats representing a color

    if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true
                                 // when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                io.Framerate);

    ImGui::End();
}

void ImguiEndFrame(/*GLFWwindow *window */) {

    // ImGuiIO &io = ImGui::GetIO();

    // generates vertex buffers from the drawing layout commands
    ImGui::Render();

    // int width, height;
    // window::GetSize(window, &width, &height);
    // io.DisplaySize = ImVec2(width, height);

    // TODO: needs to be in a different branch to get these features
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     GLFWwindow *backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }

    // submits the vertex buffers directly to glad loaded opengl pipeline
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiShutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
} // namespace imgui
} // namespace core
