#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;

void main() {
    v_uv = a_uv;
    gl_Position = vec4(pos.x, pos.y, 0, 1);
}