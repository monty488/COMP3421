// COMP3421 Assignment 1
// by Zahin Ali z5312404

// C++17 doesn't have std::pi
#define _USE_MATH_DEFINES
#include <cmath>

#include <cstdlib>
#include <chrono>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chicken3421/chicken3421.hpp>
#include <iostream>


struct image_t {
    int width;
    int height;
    int n_channels; // 3 if rgb; 4 if rgba
    void *data;
};

struct vertex_t {
    glm::vec2 pos;
    glm::vec2 uv;
};

struct mesh_t {
    GLuint vao;
    GLuint vbo;
    std::vector<vertex_t> verts;
    glm::mat4 t;
    glm::mat4 r;
    glm::mat4 s;
};

image_t load_image(const std::string &filename) {
    image_t img;

    stbi_set_flip_vertically_on_load(true);
    img.data = stbi_load(filename.data(), &img.width, &img.height, &img.n_channels, 0);

    chicken3421::expect(img.data, "Could not read " + filename);

    return img;
}

GLuint make_texture(const std::string &path) {
    image_t tex_img = load_image(path);

    GLint format = tex_img.n_channels == 3 ? GL_RGB : GL_RGBA; // assuming that if not 3 channels then 4

    GLuint tex;
    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, format, tex_img.width, tex_img.height, 0, format, GL_UNSIGNED_BYTE, tex_img.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

mesh_t make_mesh(float xmax, float ymax, float xmin, float ymin) {

	std::vector<vertex_t> verts {
        {{xmax, ymax}, {1,1}},    // top-right 
        {{xmax, ymin}, {1,0}},  // bottom-right
        {{xmin, ymin}, {0,0}}, // bottom-left

        {{xmax, ymax}, {1,1}},    // top-right
        {{xmin, ymin}, {0,0}}, // bottom-left
        {{xmin, ymax}, {0,1}},   // top-left
	};

    
    GLuint vao = chicken3421::make_vao();

    GLuint vbo = chicken3421::make_buffer();

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLintptr)(sizeof(vertex_t) * verts.size()), verts.data(), GL_STATIC_DRAW);

    // attrib 0 :: position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *)(offsetof(vertex_t, pos)));

    // attrib 1 :: uv (texture coordinates)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *)(offsetof(vertex_t, uv)));

    glm::mat4 t = glm::identity<glm::mat4>();
    glm::mat4 r = glm::identity<glm::mat4>();
    glm::mat4 s = glm::identity<glm::mat4>();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return {vao, vbo, verts, t, r, s};
}

void delete_mesh(mesh_t mesh) {
    mesh.verts.clear();
    chicken3421::delete_buffer(mesh.vbo);
    chicken3421::delete_vao(mesh.vao);
}

int main() {
    auto success = glfwInit();
    GLFWwindow *win = chicken3421::make_opengl_window(1280, 720, "Assignment 1 z5312404");

    chicken3421::make_opengl_context(win);

    GLuint vshader = chicken3421::make_shader("res/shaders/sprite_vert.glsl", GL_VERTEX_SHADER);

    GLuint fshader = chicken3421::make_shader("res/shaders/frag.glsl", GL_FRAGMENT_SHADER);

    GLuint bg_vshader = chicken3421::make_shader("res/shaders/bg_vert.glsl", GL_VERTEX_SHADER);

    GLuint program = chicken3421::make_program(vshader, fshader);
    GLuint bg_program = chicken3421::make_program(bg_vshader, fshader);


    chicken3421::delete_shader(vshader);
    chicken3421::delete_shader(fshader);

    // create the meshes
    mesh_t cloud = make_mesh(0.25, 0.5, -0.25, -0.5);
    mesh_t barret = make_mesh(0.25, 0.5, -0.25, -0.5);
    mesh_t tifa = make_mesh(0.25, 0.5, -0.25, -0.5);
    mesh_t sephiroth = make_mesh(0.45, 0.4, -0.05, -0.6);
    mesh_t background = make_mesh(1, 1, -1, -1);

    // Enable blending for transparent textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create the textures
    GLuint cloud_tex1 = make_texture("res/img/cloud/cloud_01.png");
    GLuint cloud_tex2 = make_texture("res/img/cloud/cloud_02.png");
    GLuint cloud_tex3 = make_texture("res/img/cloud/cloud_03.png");
    GLuint cloud_tex4 = make_texture("res/img/cloud/cloud_04.png");

    GLuint barret_tex1 = make_texture("res/img/barret/barret_01.png");
    GLuint barret_tex2 = make_texture("res/img/barret/barret_02.png");
    GLuint barret_tex3 = make_texture("res/img/barret/barret_03.png");
    GLuint barret_tex4 = make_texture("res/img/barret/barret_04.png");

    GLuint tifa_tex1 = make_texture("res/img/tifa/tifa_01.png");
    GLuint tifa_tex2 = make_texture("res/img/tifa/tifa_02.png");
    GLuint tifa_tex3 = make_texture("res/img/tifa/tifa_03.png");
    GLuint tifa_tex4 = make_texture("res/img/tifa/tifa_04.png");

    GLuint sephiroth_tex = make_texture("res/img/sephiroth.png");
    
    GLuint bg = make_texture("res/img/background.png");


    glUseProgram(program);
    GLint loc_tex = glGetUniformLocation(program, "u_tex");
    GLint loc_matrix = glGetUniformLocation(program, "u_matrix");

    // Variables created for texture animation
    int texture_loop = 0;
    double anim_delay = 0;
    GLint current_texture_cloud;
    GLint current_texture_barret;
    GLint current_texture_tifa;

    while (!glfwWindowShouldClose(win)) {

        // Time variable for the animations
        double current_time = glfwGetTime();

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);
        glActiveTexture(GL_TEXTURE0);

        // Display the background
        glUseProgram(bg_program);
        glBindVertexArray(background.vao);
        glBindTexture(GL_TEXTURE_2D, bg);
        
        glDrawArrays(GL_TRIANGLES, 0, 10);
        glUseProgram(program);

        // Sets the scale and translate matrices for sephiroth mesh
        sephiroth.s = glm::scale(glm::identity<glm::mat4>(), glm::vec3{1.7, 1.7, 0});
        sephiroth.t = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-0.75, 0.2 + glm::sin(glfwGetTime()) * 0.20, 0));

        // Display sephiroth mesh
		glBindVertexArray(sephiroth.vao);
        glBindTexture(GL_TEXTURE_2D, sephiroth_tex);
        glUniformMatrix4fv(loc_matrix, 1, GL_FALSE, glm::value_ptr(sephiroth.t * sephiroth.s));
        glDrawArrays(GL_TRIANGLES, 0, 10);
       
        // Checks the time, and determines which texture for each of the 
        // 3 animated meshes should be displayed at the given time
        // as well as sets the time for when the next texture will be
        // displayed
        if (current_time > anim_delay) {
            anim_delay = current_time + 0.2;
            switch (texture_loop) {
                case 1:   
                    current_texture_cloud = cloud_tex1;
                    current_texture_barret = barret_tex1;
                    current_texture_tifa = tifa_tex1;
                    texture_loop++;
                    break;
                case 2:
                    current_texture_cloud = cloud_tex2;
                    current_texture_barret = barret_tex2;
                    current_texture_tifa = tifa_tex2;
                    texture_loop++;
                    break;
                case 3:
                    current_texture_cloud = cloud_tex3;
                    current_texture_barret = barret_tex3;
                    current_texture_tifa = tifa_tex3;
                    texture_loop++;
                    break;
                default:
                    current_texture_cloud = cloud_tex4;
                    current_texture_barret = barret_tex4;
                    current_texture_tifa = tifa_tex4;
                    texture_loop = 1;
                    break;                    
            };
        }

        // Set the scale and translate matrices for cloud, barret and tifa meshes
        cloud.s = glm::scale(glm::identity<glm::mat4>(), glm::vec3{0.70, 0.70, 0});
        cloud.t = glm::translate(glm::identity<glm::mat4>(), glm::vec3(+0.5, -0.5, 0));

        barret.s = glm::scale(glm::identity<glm::mat4>(), glm::vec3{0.70, 0.70, 0});
        barret.t = glm::translate(glm::identity<glm::mat4>(), glm::vec3(+0.7, -0.3, 0));

        tifa.s = glm::scale(glm::identity<glm::mat4>(), glm::vec3{0.50, 0.50, 0});
        tifa.t = glm::translate(glm::identity<glm::mat4>(), glm::vec3(+0.7, -0.7, 0));


        // Display the meshes for cloud, barret and tifa
        glBindVertexArray(barret.vao);
        glBindTexture(GL_TEXTURE_2D, current_texture_barret);
        glUniformMatrix4fv(loc_matrix, 1, GL_FALSE, glm::value_ptr(barret.t * barret.s));
        glDrawArrays(GL_TRIANGLES, 0, 10);

        glBindVertexArray(tifa.vao);
        glBindTexture(GL_TEXTURE_2D, current_texture_tifa);
        glUniformMatrix4fv(loc_matrix, 1, GL_FALSE, glm::value_ptr(tifa.t * tifa.s));
        glDrawArrays(GL_TRIANGLES, 0, 10);
        
        glBindVertexArray(cloud.vao);
        glBindTexture(GL_TEXTURE_2D, current_texture_cloud);
        glUniformMatrix4fv(loc_matrix, 1, GL_FALSE, glm::value_ptr(cloud.t * cloud.s));
        glDrawArrays(GL_TRIANGLES, 0, 10);

        glUniform1i(loc_tex, 0);
        glfwSwapBuffers(win);

    }


    // Tear down
    delete_mesh(background);
    delete_mesh(cloud);
    delete_mesh(barret);
    delete_mesh(tifa);
    delete_mesh(sephiroth);
    chicken3421::delete_texture(bg);
    chicken3421::delete_texture(sephiroth_tex);
    chicken3421::delete_texture(cloud_tex1);
    chicken3421::delete_texture(cloud_tex2);
    chicken3421::delete_texture(cloud_tex3);
    chicken3421::delete_texture(cloud_tex4);
    chicken3421::delete_texture(barret_tex1);
    chicken3421::delete_texture(barret_tex2);
    chicken3421::delete_texture(barret_tex3);
    chicken3421::delete_texture(barret_tex4);
    chicken3421::delete_texture(tifa_tex1);
    chicken3421::delete_texture(tifa_tex2);
    chicken3421::delete_texture(tifa_tex3);
    chicken3421::delete_texture(tifa_tex4);
    chicken3421::delete_program(bg_program);
    chicken3421::delete_program(program);
    chicken3421::delete_shader(fshader);
    chicken3421::delete_shader(vshader);
    chicken3421::delete_shader(bg_vshader);
    glfwDestroyWindow(win);

    return EXIT_SUCCESS;
}


