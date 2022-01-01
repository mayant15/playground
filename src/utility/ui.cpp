#include "ui.h"

#include <array>

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

            ImGui::Separator();
            ImGui::Text("Render Settings");
            ImGui::Separator();

            static std::array<std::string, 2> items = {
                "SolidMaterial",
                "PhongMaterial"
            };

            std::string combo_preview_value = config.shader_type;
            if (ImGui::BeginCombo("Material", combo_preview_value.c_str(), 0))
            {
                for (int n = 0; n < items.size(); n++)
                {
                    const bool is_selected = (items[n] == config.shader_type);
                    if (ImGui::Selectable(items[n].c_str(), is_selected))
                        config.shader_type = items[n];

                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::Checkbox("Wireframe", &config.wireframe);

            ImGui::Text("Clear color");
            ImGui::ColorEdit3("ClearColor##1", (float *)&config.clear_color, 0);

            ImGui::Text("Fill color");
            ImGui::ColorEdit3("FillColor##1", (float *)&config.fill_color, 0);

            ImGui::Separator();
            ImGui::Text("Light Settings");
            ImGui::Separator();

            ImGui::DragFloat3("Position##Light", config.light_pos);
            ImGui::ColorEdit3("Ambient", (float *)&config.ambient);

            ImGui::Separator();
            ImGui::Text("Camera Settings");
            ImGui::Separator();

            ImGui::DragFloat3("Position##Camera", config.camera_pos);
            ImGui::DragFloat3("Look At", config.look_at);

            ImGui::Separator();
            ImGui::Text("Object Settings");
            ImGui::Separator();

            ImGui::DragFloat3("Position##Object", config.object_pos);
            ImGui::ColorEdit3("Albedo", (float *)&config.albedo);

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
