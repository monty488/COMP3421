#include "ass3/model.hpp"
#include "ass3/texture_2d.hpp"
#include "ass3/mesh.hpp"
#include "ass3/cubemap.hpp"
#include <tiny_obj_loader.h>
#include <chicken3421/chicken3421.hpp>

namespace model {
	mesh::mesh_t make_mesh(
			const std::vector<glm::vec4> &positions,
			const std::vector<glm::vec2> &texcoords,
			const std::vector<glm::vec3> &normals,
			int material_id
	) {
		GLuint vao = chicken3421::make_vao();
		glBindVertexArray(vao);

		GLuint vbo = chicken3421::make_buffer();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLsizeiptr pos_sz = positions.size() * sizeof(glm::vec4);
		GLsizeiptr tc_sz = texcoords.size() * sizeof(glm::vec2);
		GLsizeiptr nrm_sz = normals.size() * sizeof(glm::vec3);
		glBufferData(
				GL_ARRAY_BUFFER,
				pos_sz + tc_sz + nrm_sz,
				nullptr,
				GL_STATIC_DRAW
		);
		glBufferSubData(GL_ARRAY_BUFFER, 0, pos_sz, positions.data());
		glBufferSubData(GL_ARRAY_BUFFER, pos_sz, tc_sz, texcoords.data());
		glBufferSubData(GL_ARRAY_BUFFER, pos_sz + tc_sz, nrm_sz, normals.data());

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) pos_sz);
		if (nrm_sz != 0) {
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (pos_sz + tc_sz));
		}

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		if (nrm_sz != 0) glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mesh::mesh_t current_mesh;
		current_mesh.vao = vao;
		current_mesh.vbo = vbo;
		current_mesh.nverts = (GLuint)positions.size();
		current_mesh.material_id = material_id;


		return current_mesh;
	}
	model_t load(const std::string& path) {
		tinyobj::ObjReader reader;
		tinyobj::ObjReaderConfig config{};
		config.triangulate = true;
		config.mtl_search_path = path.substr(0, path.find_last_of('/') + 1);

		bool did_load = reader.ParseFromFile(path, config);
		chicken3421::expect(did_load && reader.Error().empty() && reader.Warning().empty(),
		                    reader.Error() + reader.Warning());

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();
		auto& materials = reader.GetMaterials();
		auto model = model_t{};

		std::vector<material_t> mats;
		// initialise the materials
		for (const auto& m : materials) {
			auto mat = material_t{};
			mat.diffuse = glm::vec4{m.diffuse[0], m.diffuse[1], m.diffuse[2], 1.0f};
			mat.diffuse_map = m.diffuse_texname.empty()
			                     ? 0
			                     : texture_2d::init(config.mtl_search_path + m.diffuse_texname);
			mat.specular = glm::vec3{m.specular[0], m.specular[1], m.specular[2]};
			mat.specular_map = m.specular_texname.empty()
			                      ? 0
			                      : texture_2d::init(config.mtl_search_path + m.diffuse_texname);
			mats.push_back(mat);
		}

		// initialise the static meshes
		for (const auto& shape : shapes) {
			mesh::mesh_template_t mesh_template;
			for (const auto& index : shape.mesh.indices) {
				const float* pos = &attrib.vertices[3 * index.vertex_index];
				mesh_template.positions.emplace_back(pos[0], pos[1], pos[2]);
				if (!attrib.texcoords.empty()) {
					const float* tc = &attrib.texcoords[2 * index.texcoord_index];
					mesh_template.tex_coords.emplace_back(tc[0], tc[1]);
				}
				if (!attrib.normals.empty()) {
					const float* norm = &attrib.normals[3 * index.normal_index];
					mesh_template.normals.emplace_back(norm[0], norm[1], norm[2]);
				}
			}
			model.meshes.push_back(mesh::init(mesh_template));
			model.materials.push_back(mats[shape.mesh.material_ids[0]]);
		}
		return model;
	}

	void destroy(const model_t& model) {
		for (auto const& mesh : model.meshes) {
			mesh::destroy(mesh);
		}
		for (auto const& mat : model.materials) {
			texture_2d::destroy(mat.diffuse_map);
			texture_2d::destroy(mat.specular_map);
		}
	}

	screen_quad_t make_screen_quad(GLuint scene_tex) {
		glm::vec4 positions[] = {
				{-1, -1, 0, 1},
				{1, -1, 0, 1},
				{1, 1, 0, 1},
				{-1, 1, 0, 1}
		};

		glm::vec2 texcoords[] = {
				{0, 0},
				{1, 0},
				{1, 1},
				{0, 1}
		};

		const auto n_verts = 6;
		GLuint indices[] = {
				0, 1, 2,
				0, 2, 3
		};

		GLuint vao = chicken3421::make_vao();
		glBindVertexArray(vao);

		GLuint vbo = chicken3421::make_buffer();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(texcoords), nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(texcoords), texcoords);

		GLuint ibo = chicken3421::make_buffer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)sizeof(positions));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



		return {vao, vbo, ibo, n_verts, {scene_tex}};
	}
	model_t generate_sphere() {
		int stacks = 16;
		int slices = 32;

		struct sphere_vertex_t {
			glm::vec3 pos;
			glm::vec3 normal;
			glm::vec2 texco;
		};

		std::vector<sphere_vertex_t> sverts;
		for (int i = 0; i <= stacks; ++i) {
			double phi = glm::pi<double>() * i / (double) stacks;

			for (int j = 0; j <= slices; ++j) {
				double theta = 2 * glm::pi<double>() * j / (double) slices;

				glm::vec3 p = { std::cos(theta) * std::sin(phi), std::cos(phi), std::sin(theta) * std::sin(phi) };
				glm::vec3 normal = glm::normalize(p);
				glm::vec2 tc = { (float) -j / (float) slices, (float) i / (float) stacks };

				sverts.push_back(sphere_vertex_t { p, normal, tc });
			}
		}

		std::vector<glm::vec4> positions;
		std::vector<glm::vec2> texcoords;
		std::vector<glm::vec3> normals;

		// sorry
		auto push_vert = [&](int i) {
			const auto& v = sverts[i];
			positions.push_back(glm::vec4(v.pos,1));
			texcoords.push_back(v.texco);
			normals.push_back(v.normal);
		};
		for (int i = 0; i < slices * stacks + stacks; ++i) {
			push_vert(i);
			push_vert(i + slices + 1);
			push_vert(i + slices);

			push_vert(i + slices + 1);
			push_vert(i);
			push_vert(i + 1);
		}

		std::vector<mesh::mesh_t> meshes;
		meshes.push_back(make_mesh(positions, texcoords, normals, 0));

		std::vector<material_t> materials;
		material_t mat;
		//mat.cube_map = cubemap::make_cubemap("res/skybox/sky");

		materials.push_back(mat);

		return { meshes, materials };
	}
} // namespace model
