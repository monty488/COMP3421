#ifndef COMP3421_RENDERER_HPP
#define COMP3421_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "scene.hpp"
#include "euler_camera.hpp"
#include "ass3/framebuffer.hpp"

namespace renderer {
	struct renderer_t {
		glm::mat4 projection;

		GLuint program;
		GLuint skybox_program;
		GLuint hdr_program;
		GLuint invert_program;

		// directional light attributes
		glm::vec3 sun_light_dir = glm::normalize(glm::vec3(0) - glm::vec3(-25, 20, -25));
		glm::vec3 sun_light_diffuse = glm::vec3(0.0f, 200.0f, 0.0f);
		glm::vec3 sun_light_ambient = glm::vec3(0.5f);
		glm::vec3 sun_light_specular = glm::vec3(1.0f);

		// spot light attributes
		glm::vec3 spot_light_pos = glm::vec3(10, 1, 0);
		glm::vec3 spot_light_diffuse = glm::vec3(1.0f);
		glm::vec3 spot_light_ambient = glm::vec3(0.5f);
		glm::vec3 spot_light_specular = glm::vec3(0, 0, 2.5f);

		glm::vec4 clip_plane = glm::vec4(0, 1, 0, -0.8);
	};

	renderer_t init(const glm::mat4& projection);

	void render(const renderer_t& renderer,
	            const euler_camera::camera_t& camera,
	            const scene::node_t& scene,
	            const model::model_t& skybox);


	void render(const renderer_t& renderer,
	            const euler_camera::camera_t& camera,
	            const scene::node_t& scene,
	            const model::model_t& skybox,
				const framebuffer::framebuffer_t &target);
	
	void post_process(const renderer_t &renderer, const model::screen_quad_t &screen_quad, bool invert_colours);
} // namespace renderer

#endif // COMP3421_RENDERER_HPP
