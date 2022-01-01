// photon-shader-display-name Solid Shader!

// photon-shader-type vertex!

#version 460 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = vec4(u_projection * u_view * u_model * vec4(a_position, 1.));
}

// photon-shader-type fragment!

#version 460 core

uniform vec4 u_color;

out vec4 frag_color;

void main() {
    frag_color = u_color;
}

