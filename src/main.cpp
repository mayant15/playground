#include <iostream>

#include "base.h"
#include "Window.h"
#include "Shader.h"

#include "utility/logger.h"
#include "utility/ui.h"

#define XYZ(VEC) VEC.x, VEC.y, VEC.z

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

    glfwSwapInterval(1);

    pg::log::info("Successfully initialized OpenGL context");

    pg::ui::init(window.get_raw_pointer());

    bool show_demo_window = true;

    // vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    // Setup VAO to store vertex data configuration
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup buffers
    unsigned int vbo;
    glGenBuffers(1, &vbo);

    // Bind and configure this as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Setup vertex shader input layout
    glVertexAttribPointer(pg::VERTEX_POSITION_LAYOUT_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(pg::VERTEX_POSITION_LAYOUT_INDEX);

    pg::ShaderConfig vertex_shader_config{};
    vertex_shader_config.filename = "D:\\code\\graphics\\playground\\src\\shaders\\identity.vert";
    vertex_shader_config.type = pg::EShaderType::VERTEX;
    pg::Shader vertex_shader{vertex_shader_config};

    pg::ShaderConfig fragment_shader_config{};
    fragment_shader_config.filename = "D:\\code\\graphics\\playground\\src\\shaders\\solid_color.frag";
    fragment_shader_config.type = pg::EShaderType::FRAGMENT;
    pg::Shader fragment_shader{fragment_shader_config};

    pg::ShaderProgram program{std::vector{&vertex_shader, &fragment_shader}};

    program.use();

    ImVec4 clear_color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 1.0f);
    ImVec4 fill_color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 1.0f / 255.0f, 1.0f);

    // Main loop
    while (!window.should_close())
    {
        pg::ui::new_frame();
        pg::ui::demo_window(show_demo_window);

        ImGui::Text("Clear color");
        ImGui::ColorEdit3("ClearColor##1", (float *)&clear_color, 0);

        ImGui::Text("Fill color");
        ImGui::ColorEdit3("FillColor##1", (float *)&fill_color, 0);

        pg::ui::finalize_frame();

        // Setup viewport
        const auto &[width, height] = window.get_dims();
        glViewport(0, 0, width, height);

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);

        program.set_vec3f("fill_color", {XYZ(fill_color)});

        glDrawArrays(GL_TRIANGLES, 0, 3);

        pg::ui::render();

        window.swap_buffers();
        pg::poll_window_events();
    }

    // Shutdown
    pg::ui::shutdown();

    return EXIT_SUCCESS;
}
