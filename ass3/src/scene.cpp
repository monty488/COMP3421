#include "ass3/scene.hpp"
#include "ass3/shapes.hpp"
#include "ass3/cubemap.hpp"
#include "ass3/texture_2d.hpp"
#include "ass3/model.hpp";
#include <iostream>

const char* SKYBOX_BASE_PATH_1 = "res/skybox/sky";
const char* STAGE_BASE_PATH = "res/obj/stage/untitled.obj";


namespace scene {
	node_t make_volume(int width,
	                   int height,
	                   int depth,
	                   model::material_t top_material,
	                   model::material_t side_material,
	                   scene::node_t::KIND top_kind,
	                   scene::node_t::KIND side_kind) {
		auto volume = scene::node_t{};

		std::vector<std::pair<int, int>> dims = {
		   {depth, height},
		   {depth, height},
		   {width, depth},
		   {width, depth},
		};

		std::vector<glm::vec3> rotations = {
		   {0, glm::radians(-90.0), 0},
		   {0, glm::radians(90.0), 0},
		   {glm::radians(90.0), 0, 0},
		   {glm::radians(-90.0), 0, 0},
		};

		std::vector<glm::vec3> translations = {
		   {-width / 2.0f, 0, depth / 2.0f},
		   {width / 2.0f, 0, depth / 2.0f},
		   {0, -height / 2.0f, depth / 2.0f},
		   {0, height / 2.0f, depth / 2.0f},
		};

		for (auto i = size_t{0}; i < 4; ++i) {
			auto side = scene::node_t{};
			auto side_template = shapes::make_plane(dims[i].first, dims[i].second);
			shapes::calc_vertex_normals(side_template);
			side.kind = side_kind;
			side.model.meshes.push_back(mesh::init(side_template));
			side.model.materials.push_back(side_material);
			side.translation = translations[i];
			side.rotation = rotations[i];
			volume.children.push_back(side);
		}

		auto top = scene::node_t{};
		auto top_template = shapes::make_plane(width, height);
		shapes::calc_vertex_normals(top_template);
		top.kind = top_kind;
		top.model.meshes.push_back(mesh::init(top_template));
		top.model.materials.push_back(top_material);
		top.translation = glm::vec3(0, 0, depth);

		volume.children.push_back(top);

		return volume;
	}

node_t make_volume_2(int width,
	                   int height,
	                   int depth,
	                   model::material_t top_material,
	                   scene::node_t::KIND top_kind) {
		auto volume = scene::node_t{};

		auto top = scene::node_t{};
		auto top_template = shapes::make_plane(width, height);
		shapes::calc_vertex_normals(top_template);
		top.kind = top_kind;
		top.model.meshes.push_back(mesh::init(top_template));
		top.model.materials.push_back(top_material);
		top.translation = glm::vec3(0, 20, depth + 5);
		top.rotation = glm::vec3(glm::radians(90.0), 0, 0);

		volume.children.push_back(top);

		return volume;
	}


	node_t
	make_glass_volume(int width, int height, int depth, GLuint refraction_map, GLuint reflection_map) {
		auto glass_surface_mat = model::material_t{
		   .diffuse_map = refraction_map,
		   .reflection_map = reflection_map,
		   .diffuse = glm::vec4(0.306, 0.69, 0.76, 0.3),
		   .specular = glm::vec3(1.0),
		   .phong_exp = 50.0f,
		   .cube_map_factor = 0.3f,
		   .reflection_map_factor = 1.0f,
		};
		auto glass_side_mat = model::material_t{.diffuse = glm::vec4(0.306, 0.69, 0.76, 0.3)};
		node_t glass_volume = make_volume(width,
		                                  height,
		                                  depth,
		                                  glass_surface_mat,
		                                  glass_side_mat,
		                                  scene::node_t::NODE,
		                                  scene::node_t::NODE);

		glass_volume.rotation.x = glm::radians(-90.0);
		return glass_volume;
	}

	node_t
	make_cube_volume(int width, int height, int depth, GLuint refraction_map, GLuint reflection_map, GLuint cube_map, scene::node_t::KIND kind) {
		auto cube_surface_mat = model::material_t{
		   .diffuse_map = refraction_map,
			.cube_map = cube_map,
		   .reflection_map = reflection_map,
		   .diffuse = glm::vec4(1.0, 1.0, 1.0, 1),
		   .specular = glm::vec3(1.0),
		   .phong_exp = 50.0f,
		   .cube_map_factor = 0.3f,
		   .reflection_map_factor = 1.0f,
		};
		node_t cube_volume = make_volume(width,
		                                  height,
		                                  depth,
		                                  cube_surface_mat,
		                                  cube_surface_mat,
		                                  kind,
		                                  kind);

		cube_volume.rotation.x = glm::radians(-90.0);
		return cube_volume;
	}

	node_t
	make_cube_volume_2(int width, int height, int depth, GLuint framebuffer_tex, scene::node_t::KIND kind) {
		auto cube_surface_mat = model::material_t{
		   .diffuse_map = framebuffer_tex,
		   .diffuse = glm::vec4(1.0, 1.0, 1.0, 1),
		   .specular = glm::vec3(1.0),
		   .phong_exp = 50.0f,
		   .cube_map_factor = 0.3f,
		   .reflection_map_factor = 1.0f,
		};
		node_t cube_volume = make_volume_2(width,
		                                  height,
		                                  depth,
		                                  cube_surface_mat,
		                                  kind);

		cube_volume.rotation.x = glm::radians(-90.0);
		return cube_volume;
	}

	node_t
	make_stage() {
		auto stage_model = model::load(STAGE_BASE_PATH);
		node_t stage = scene::node_t{};
		stage.model = stage_model;

		return stage;
	}

	model::model_t make_skybox() {
		auto skybox = model::model_t{};
		skybox.meshes.push_back(mesh::init(shapes::make_cube(1.0f)));
		skybox.materials.push_back({.cube_map = cubemap::make_cubemap(SKYBOX_BASE_PATH_1)});
		return skybox;
	}

} // namespace scene