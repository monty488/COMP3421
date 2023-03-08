#version 330 core

in vec2 v_uv;
out vec4 fs_color;
uniform sampler2D u_tex;

void main() {
    fs_color = texture(u_tex, v_uv);
}