#version 460 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 position;
out vec3 normal;

void main() {
    position = a_position;
    normal = vec3(u_model * vec4(0., 1., 0., 1.));
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.);
}
