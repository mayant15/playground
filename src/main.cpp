#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "utility/logger.h"

void glfw_error_callback(int error, const char *description)
{
    pg::log::error("[GLFW{}]: {}", error, description);
}

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    const char *glsl_version = "#version 460";

    // Initialize
    if (glfwInit() == GLFW_FALSE)
    {
        pg::log::error("Failed to initialize GLFW");
        return EXIT_FAILURE;
    }
    glfwSetErrorCallback(glfw_error_callback);

    // Create a new window and OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Playground", nullptr, nullptr);
    if (!window)
    {
        pg::log::error("Failed to create GLFW window");
        return EXIT_FAILURE;
    }
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize glad
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        pg::log::error("Failed to initialize glad");
        return EXIT_FAILURE;
    }

    pg::log::info("Successfully initialized OpenGL context");

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

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5, 0.7, 0.4, 1.0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        // Prepare the UI for render
        ImGui::NewFrame();

        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
