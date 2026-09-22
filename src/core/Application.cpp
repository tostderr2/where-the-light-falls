#include "Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_int2.hpp>

#include "Log.h"
#include "Window.h"
#include "game/Game.h"

namespace core {
inline void imguiInit(Application *window);
inline void imguiDraw();
inline void imguiStartFrame();
inline void imguiEndFrame(Application *app);
inline void imguiShutdown();

Application::Application() {
    // TODO: change this to higher number one's tested by hiting all buttons and mouse
    // reserving a block of memory for events
    m_eventBuff.events.reserve(10);
}

Application::~Application() {
    // window::Destroy(&m_window);
}

void Application::Init() {

    window::Create(&m_window, 1080, 720, "Where the light falls", &m_eventBuff);
    window::SetCallbacks(&m_window, &m_eventBuff);
    LOG_CORE_INFO("Created window");

    imguiInit(this);
}
Window *Application::GetWindow() {
    return &m_window;
}

void Application::Run() {
    // TODO: remove the filler dt and write a simple impl
    float lastCheckedTime = glfwGetTime();

    while (m_running) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastCheckedTime;
        lastCheckedTime = currentTime;

        if (window::ShouldClose(&m_window)) {
            m_running = false;
        }

        window::PollEvents();

        imguiStartFrame();
        imguiDraw();
        // // update state
        // game::OnUpdate(deltaTime, m_game);
        // // render
        // game::OnRender(m_game);

        imguiEndFrame(this);

        window::SwapBuffers(&m_window);
        eventbuffer::Clear(&m_eventBuff);
    }

    imguiShutdown();
    window::Destroy(&m_window);
}

inline void imguiInit(Application *app) {
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

    GLFWwindow *window = app->GetWindow()->glfwWindow;
    CORE_ASSERT(ImGui_ImplGlfw_InitForOpenGL(window, true), "ImGui Glfw Init for OpenGl failed!");
    CORE_ASSERT(ImGui_ImplOpenGL3_Init("#version 410"), "ImGui Glfw Init for OpenGl failed!");

    LOG_CORE_INFO("imgui initialised and started new frame");
}

inline void imguiStartFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

inline void imguiDraw() {
    ImGuiIO &io = ImGui::GetIO();
    static bool show_demo_window = true;
    ImGui::Begin("Debug Menu");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                io.Framerate);

    static float color[3] = {0.1f, 0.1f, 0.1f};
    ImGui::ColorEdit3("Background Color", color); // live color picker

    ImGui::End();

    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
}

inline void imguiEndFrame(Application *app) {

    ImGuiIO &io = ImGui::GetIO();

    // generates vertex buffers from the drawing layout commands
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    Window *window = app->GetWindow();
    int width, height;
    window::GetSize(window, &width, &height);
    io.DisplaySize = ImVec2(width, height);

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

inline void imguiShutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
} // namespace core
