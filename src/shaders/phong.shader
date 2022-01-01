// photon-shader vertex!

#version 460 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 position;
out vec3 normal;

void main() {
    position = vec3(u_model * vec4(a_position, 1.));
    normal = mat3(transpose(inverse(u_model))) * a_normal;
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.);
}


// photon-shader fragment!

#version 460 core

in vec3 position;
in vec3 normal;

uniform vec4 u_ambient;
uniform vec4 u_albedo;
uniform vec3 u_light_pos;
// uniform vec3 u_light_color;
// uniform float u_roughness;
// uniform float u_shininess;

out vec4 frag_color;

void main()
{
    vec3 N = normalize(normal);
    vec3 L = normalize(u_light_pos - position);
    float diffuse = max(dot(N, L), 0.0);
    frag_color = diffuse * u_albedo + u_ambient;
}

