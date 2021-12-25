#include "ui.h"

namespace pg::ui
{

    void init(GLFWwindow *window)
    {
        const char *glsl_version = "#version 460";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Load Fonts
        io.Fonts->AddFontDefault();
    }

    void new_frame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        // Prepare the UI for render
        ImGui::NewFrame();
    }

    void demo_window(bool &show)
    {
        if (show)
        {
            ImGui::ShowDemoWindow(&show);
        }
    }

    void finalize_frame()
    {
        ImGui::Render();
    }

    void render()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

} // namespace pg::ui
