#version 460 core

in vec3 position;
in vec3 normal;

out vec4 frag_color;

uniform vec4 fill_color;

void main()
{
    frag_color = fill_color;
}
