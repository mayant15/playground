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

    void user_config(UserConfig &config, bool &show)
    {
        if (show)
        {
            ImGui::Begin("User Config Controls", &show);

            ImGui::Checkbox("Wireframe", &config.wireframe);

            ImGui::Text("Clear color");
            ImGui::ColorEdit3("ClearColor##1", (float *)&config.clear_color, 0);

            ImGui::Text("Fill color");
            ImGui::ColorEdit3("FillColor##1", (float *)&config.fill_color, 0);

            ImGui::End();
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
