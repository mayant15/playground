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
