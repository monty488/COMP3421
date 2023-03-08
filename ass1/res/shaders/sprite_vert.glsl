#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;

uniform mat4 u_matrix;

void main() {
    v_uv = a_uv;
    gl_Position = u_matrix * vec4(pos.x, pos.y, 0, 1);
}