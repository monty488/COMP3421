#ifndef COMP3421_SCENE_HPP
#define COMP3421_SCENE_HPP

#include "model.hpp"
#include "euler_camera.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace scene {
	struct node_t {
		enum KIND {
			EMPTY,
			STATIC_MESH,
			REFLECTIVE,
			GLASS_SURFACE,
			BLACK_WHITE_SCREEN,
			NODE,
		} kind = EMPTY;
		model::model_t model;
		glm::vec3 translation = glm::vec3(0.0);
		glm::vec3 rotation = glm::vec3(0.0); // vec3 of euler angles
		glm::vec3 scale = glm::vec3(1.0);
		std::vector<node_t> children;
		glm::vec2 polygon_offset = glm::vec2(0.0); // (factor, units)
		bool invisible = false;
	};

	node_t make_marccoin();

	node_t make_stage();

	node_t make_plane(int width, int height, int depth);

	node_t make_glass_volume(int width,
	                         int height,
	                         int depth,
	                         GLuint refraction_map = 0,
	                         GLuint reflection_map = 0);

	node_t make_cube_volume(int width,
	                         int height,
	                         int depth,
	                         GLuint refraction_map = 0,
	                         GLuint reflection_map = 0,
							 GLuint cube_map = 0,
							 node_t::KIND kind = node_t::NODE);

	node_t make_cube_volume_2(int width, int height, int depth, GLuint framebuffer_tex, scene::node_t::KIND kind);




	model::model_t make_skybox();

	node_t make_sphere();

} // namespace scene

#endif // COMP3421_SCENE_HPP
