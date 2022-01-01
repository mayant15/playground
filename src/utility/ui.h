#pragma once

#include <base.h>

namespace pg::ui
{
    struct UserConfig
    {
        ImVec4 clear_color = ImVec4(0.3, 0.3, 0.3, 0.3);
        ImVec4 fill_color = ImVec4(1.0, 1.0, 1.0, 1.0);
        bool wireframe = false;

        // Light params
        float light_pos[3] = {2.0, 2.0, 2.0};
        ImVec4 ambient = {0.01, 0.01, 0.01, 1.0};

        // Camera
        float look_at[3] = {0.0, 0.0, 0.0};
        float camera_pos[3] = {0.0, 0.0, 5.0};

        // Object
        float object_pos[3] = {0.0, 0.0, 0.0};
        ImVec4 albedo = {0.6, 0.7, 0.2, 1.0};

        // Material
        std::string shader_type;
    };

    void init(GLFWwindow *window);
    void new_frame();
    void demo_window(bool &show);
    void user_config(UserConfig &config, bool &show);
    void finalize_frame();
    void render();
    void shutdown();

} // namespace pg::ui
