#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "utility/logger.h"

int main(void)
{
    glm::vec3 v{0, 1, 2};

    pg::log::info("Hello World!");
    pg::log::warn("({},{},{})", v.x, v.y, v.z);
    pg::log::error("Fatal failure");
    return 0;
}
