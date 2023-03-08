#version 330 core

in vec3 v_pos;
in vec3 v_normal;
in vec2 v_texco;

uniform sampler2D u_diff_map;
uniform sampler2D u_spec_map;

// Lighting parameters
uniform vec3 u_light_pos_1;
uniform vec3 u_light_color_1;
uniform vec3 u_light_pos_2;
uniform vec3 u_light_color_2;
uniform mat4 v;


// Material parameters
uniform vec3 u_diffuse;
uniform vec3 u_emissive;
uniform float u_shininess;



out vec4 color;

void main() {

    vec3 directional_light_dir = -normalize(vec3(0,-1,0));
    vec3 direction_light_diffuse_col = vec3(0.0, 0.0, 0.2);

    vec3 normal = normalize(v_normal);
    vec3 view_point_light_pos_1 = (v * vec4(u_light_pos_1, 1)).xyz;
    vec3 view_point_light_pos_2 = (v * vec4(u_light_pos_2, 1)).xyz;
    vec3 point_light_dir_1 = normalize(view_point_light_pos_1 - v_pos);
    float point_light_dist_1 = length(view_point_light_pos_1 - v_pos);
    vec3 point_light_dir_2 = normalize(view_point_light_pos_2 - v_pos);
    float point_light_dist_2 = length(view_point_light_pos_2 - v_pos);
    vec3 view_dir = normalize(-v_pos);
    vec3 reflection_1 = reflect(-point_light_dir_1, normal);
    vec3 reflection_2 = reflect(-point_light_dir_2, normal);


    vec3 diff_col = u_diffuse * texture(u_diff_map, v_texco).rgb;


    // initial accumulator color of black
    vec3 color_rgb = vec3(0, 0, 0);
    

    // add diffuse lighting of directional light
    float dir_light_diffuse_factor = clamp(dot(normal, directional_light_dir), 0, 1);
    color_rgb += direction_light_diffuse_col * dir_light_diffuse_factor;

    // add diffuse lighting of point lights
    vec3 diffuse_1 = diff_col * max(dot(normal, point_light_dir_1), 0) * u_light_color_1;
    vec3 diffuse_2 = diff_col * max(dot(normal, point_light_dir_2), 0) * u_light_color_2;

    vec3 specular_1 = texture(u_spec_map, v_texco).rgb * pow(max(dot(view_dir, reflection_1), 0), u_shininess) * u_light_color_1;
    vec3 specular_2 = texture(u_spec_map, v_texco).rgb * pow(max(dot(view_dir, reflection_2), 0), u_shininess) * u_light_color_2;

    // calculate point light contribution
    float attenuation_1 = 1 / (1 + 0.11 * point_light_dist_1);
    float attenuation_2 = 1 / (1 + 0.11 * point_light_dist_2);

    color_rgb += (diffuse_1 + specular_1) * attenuation_1;
    color_rgb += (diffuse_2 + specular_2) * attenuation_2;


    color_rgb += u_emissive;


    color = vec4(color_rgb, 1);
}
