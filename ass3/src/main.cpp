#include <thread>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <chicken3421/chicken3421.hpp>

#include <ass3/memes.hpp>
#include "ass3/scene.hpp"
#include "ass3/renderer.hpp"
#include "ass3/framebuffer.hpp"
#include "ass3/cubemap.hpp"
#include <iostream>

/**
 * Returns the difference in time between when this function was previously called and this call.
 * @return A float representing the difference between function calls in seconds.
 */
float time_delta();

/**
 * Returns the current time in seconds.
 * @return Returns the current time in seconds.
 */
float time_now();

void update_filter_on_off_cb(GLFWwindow *win, int key, int, int action, int) {
    bool *use_filter = (bool *) glfwGetWindowUserPointer(win);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        *use_filter = !*use_filter;
    }
}

void update_scene(GLFWwindow* window, float dt, scene::node_t& scene) {
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		scene.rotation.y += dt * 0.1;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		scene.rotation.y -= dt * 0.1;
	}
}

int main() {
    GLFWwindow *win = marcify(chicken3421::make_opengl_window(1280, 720, "Assignment 3"));
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    auto scene = scene::node_t{};
    int fbo_width, fbo_height;
    glfwGetFramebufferSize(win, &fbo_width, &fbo_height);
    auto screen_buffer = framebuffer::make_framebuffer(fbo_width, fbo_height);

    auto back_screen_buffer = framebuffer::make_framebuffer(fbo_width, fbo_height);
    model::screen_quad_t screen_quad = model::make_screen_quad(screen_buffer.texture);
    auto cube_map = cubemap::make_cubemap("res/skybox/sky");
    scene.children.push_back(scene::make_stage());
    scene.children.push_back(scene::make_cube_volume(3, 3, 3, 0, 0, cube_map, scene::node_t::REFLECTIVE));
    auto black_white_screen = scene::make_cube_volume_2(15, 7, 1, back_screen_buffer.texture, scene::node_t::BLACK_WHITE_SCREEN);
    scene.children.push_back(black_white_screen);


    auto camera = euler_camera::make_camera({0, 10, 20}, {0, 0, 0});


    //auto cubemap_camera = euler_camera::make_camera({0, 5, 0}, {1, 5, 0});
    //cubemap_camera.yaw = 0;

	auto renderer = renderer::init(
	   glm::perspective(glm::radians(60.0), (double)1280 / (double)720, 0.1, 1000.0));

    auto skybox = scene::make_skybox();
    bool invert_colours = false;
    glfwSetWindowUserPointer(win, &invert_colours);
    glfwSetKeyCallback(win, update_filter_on_off_cb);

    while (!glfwWindowShouldClose(win)) {
        float dt = time_delta();
        euler_camera::update_camera(camera, win, dt);


        glBindFramebuffer(GL_FRAMEBUFFER, back_screen_buffer.fbo);
        auto screen_cam = camera;
        scene.children[2].invisible = true;
        renderer::render(renderer, screen_cam, scene, skybox);
        scene.children[2].invisible = false;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glfwSwapBuffers(win);
        glfwPollEvents();

		//glEnable(GL_CLIP_DISTANCE0);
        renderer::render(renderer, camera, scene, skybox, screen_buffer);
        renderer::post_process(renderer, screen_quad, invert_colours);
		//glDisable(GL_CLIP_DISTANCE0);


    }

    // deleting the whole window also removes the opengl context, freeing all our memory in one fell swoop.
    chicken3421::delete_opengl_window(win);

    return EXIT_SUCCESS;
}


float time_delta() {
    static float then = time_now();
    float now = time_now();
    float dt = now - then;
    then = now;
    return dt;
}

float time_now() {
    return (float) glfwGetTime();
}
