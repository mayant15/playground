#include <iostream>

#include "VertexArrayInfo.h"
#include "Window.h"
#include "base.h"
#include "constants.h"
#include "materials/SolidMaterial.h"

#include "geometry/Cube.h"
#include "geometry/Rectangle.h"

#include "utility/errors.h"
#include "utility/logger.h"
#include "utility/pgmath.h"
#include "utility/ui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <photon/photon.h>

auto inner_main(void) -> void
{
    photon::Instance photon{};

    pg::Window window{pg::WindowOp{}};

    window.set_current();

    // Initialize glad
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        throw pg::Error{"Failed to initialize glad"};
    }

    // v-sync
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    pg::log::info("Successfully initialized OpenGL context");

    pg::ui::init(window.get_raw_pointer());

    bool show_demo_window = true;

    // auto vertex_info = pg::create_rectangle_vertex_info();
    auto vertex_info = pg::create_cube_vertex_info();

    auto solid_shader = photon.res.shaders.get("D:\\code\\graphics\\playground\\src\\shaders\\solid.shader");
    auto phong_shader = photon.res.shaders.get("D:\\code\\graphics\\playground\\src\\shaders\\phong.shader");

    auto material = new pg::SolidMaterial(solid_shader);

    pg::ui::UserConfig user_config{};
    user_config.shader_type = solid_shader->get_display_name();

    const auto reload_shaders_callback = [&material](int key) {
        if (key == GLFW_KEY_R)
        {
            material->reload();
        }
    };
    window.add_key_press_callback(reload_shaders_callback);

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

        glm::mat4 model(1.0);
        model = glm::translate(model, to_vec3_from_array(user_config.object_pos));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::lookAt(
            to_vec3_from_array(user_config.camera_pos),
            to_vec3_from_array(user_config.look_at),
            glm::vec3{0.0, 1.0, 0.0});

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 100.0f);

        solid_shader->use();

        material->color = photon::Color{XYZW(user_config.fill_color)};
        material->set_inputs();

        solid_shader->set_mat4f("u_model", model);
        solid_shader->set_mat4f("u_view", view);
        solid_shader->set_mat4f("u_projection", projection);

        vertex_info.render();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Render the UI on top
        pg::ui::render();

        window.swap_buffers();
        pg::poll_window_events();
    }

    photon.res.shaders.clear();
    delete material;

    // Shutdown
    pg::ui::shutdown();
}

auto main() -> int
{
    try
    {
        inner_main();
        return EXIT_SUCCESS;
    }
    catch (const pg::Error &e)
    {
        pg::log::error(e.what());
        return EXIT_FAILURE;
    }
}
