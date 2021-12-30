#include <iostream>

#include "base.h"
#include "Window.h"
#include "Shader.h"
#include "VertexArrayInfo.h"

#include "utility/logger.h"
#include "utility/ui.h"
#include "utility/pgmath.h"

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

    pg::log::info("Successfully initialized OpenGL context");

    pg::ui::init(window.get_raw_pointer());

    bool show_demo_window = true;

    // vertices and indices
    std::vector<pg::vertex_t> vertices = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    std::vector<pg::index_t> indices = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    pg::VertexArrayInfo vertex_info{};
    vertex_info
        .add_vertex_array(vertices)
        .add_indices_array(indices)
        .layout_vertices(pg::VERTEX_POSITION_LAYOUT_INDEX);

    pg::ShaderConfig vertex_shader_config{};
    vertex_shader_config.filename = "D:\\code\\graphics\\playground\\src\\shaders\\identity.vert";
    vertex_shader_config.type = pg::EShaderType::VERTEX;
    pg::Shader vertex_shader{vertex_shader_config};

    pg::ShaderConfig fragment_shader_config{};
    fragment_shader_config.filename = "D:\\code\\graphics\\playground\\src\\shaders\\solid_color.frag";
    fragment_shader_config.type = pg::EShaderType::FRAGMENT;
    pg::Shader fragment_shader{fragment_shader_config};

    pg::ShaderProgram program{std::vector{&vertex_shader, &fragment_shader}};

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

        glClear(GL_COLOR_BUFFER_BIT);

        if (user_config.wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        program.use();
        program.set_vec3f("fill_color", {XYZ(user_config.fill_color)});

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
