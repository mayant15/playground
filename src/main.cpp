#include <iostream>

#include "base.h"
#include "constants.h"
#include "Window.h"
#include "Shader.h"
#include "VertexArrayInfo.h"

#include "shaders/SolidShader.h"

#include "geometry/Rectangle.h"
#include "geometry/Cube.h"

#include "utility/logger.h"
#include "utility/ui.h"
#include "utility/pgmath.h"

#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    pg::Window window{};
    pg::WindowOp window_op{};

    if (window.init(window_op))
    {
        pg::log::error("Failed to create window");
        return EXIT_FAILURE;
    }

    window.set_current();

    // Initialize glad
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        pg::log::error("Failed to initialize glad");
        return EXIT_FAILURE;
    }

    // v-sync
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    pg::log::info("Successfully initialized OpenGL context");

    pg::ui::init(window.get_raw_pointer());

    bool show_demo_window = true;

    // auto vertex_info = pg::create_rectangle_vertex_info();
    auto vertex_info = pg::create_cube_vertex_info();

    pg::shaders::SolidShader solid_shader{};

    const auto reload_shaders_callback = [&solid_shader](int key)
    {
        if (key == GLFW_KEY_R)
        {
            solid_shader.reload();
        }
    };
    window.add_key_press_callback(reload_shaders_callback);

    pg::ui::UserConfig user_config{};

    bool show_user_config_controls = true;

    // Main loop
    while (!window.should_close())
    {
        pg::ui::new_frame();
        pg::ui::demo_window(show_demo_window);

        pg::ui::user_config(user_config, show_user_config_controls);

        pg::ui::finalize_frame();

        // Setup viewport
        const auto &[width, height] = window.get_dims();
        glViewport(0, 0, width, height);

        glClearColor(XYZW(user_config.clear_color));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (user_config.wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        solid_shader.use();

        const pg::Color fill_color{XYZW(user_config.fill_color)};

        glm::mat4 model(1.0);
        model = glm::translate(
            model,
            glm::vec3{
                user_config.object_pos[0],
                user_config.object_pos[1],
                user_config.object_pos[2],
            });
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::lookAt(
            glm::vec3{
                user_config.camera_pos[0],
                user_config.camera_pos[1],
                user_config.camera_pos[2]},
            glm::vec3{
                user_config.look_at[0],
                user_config.look_at[1],
                user_config.look_at[2]},
            glm::vec3{0.0, 1.0, 0.0});

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 100.0f);

        solid_shader.set_uniforms(
            fill_color,
            model,
            view,
            projection);

        vertex_info.render();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Render the UI on top
        pg::ui::render();

        window.swap_buffers();
        pg::poll_window_events();
    }

    // Shutdown
    pg::ui::shutdown();

    return EXIT_SUCCESS;
}
