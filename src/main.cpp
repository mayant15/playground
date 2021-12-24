#include <iostream>

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

    // Initialize glad
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        pg::log::error("Failed to initialize glad");
        return EXIT_FAILURE;
    }

    pg::log::info("Successfully initialized OpenGL context");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5, 0.7, 0.4, 1.0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Shutdown
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
