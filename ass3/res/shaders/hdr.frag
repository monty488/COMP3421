#version 330 core

uniform sampler2D u_scene;

in vec2 v_tc;

out vec4 f_color;

void main(void) {
    vec3 original_color = texture(u_scene, v_tc).rgb;
    vec3 mapped_colour = vec3(1.0) - exp(-original_color * 1.0);
    mapped_colour = pow(mapped_colour, vec3(1.0 / 2.2));

    f_color = vec4(mapped_colour, 1);
}