#pragma once

#include <glm/vec3.hpp>

#define XYZ(VEC) VEC.x, VEC.y, VEC.z
#define XYZW(VEC) VEC.x, VEC.y, VEC.z, VEC.w

inline glm::vec3 to_vec3_from_array(float arr[3])
{
    return glm::vec3{arr[0], arr[1], arr[2]};
}
