#version 460 core

out vec4 frag_color;

uniform vec3 fill_color;

void main(){
    frag_color=vec4(fill_color, 1.);
}
