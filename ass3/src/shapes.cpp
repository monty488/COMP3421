#include "ass3/mesh.hpp"
#include "ass3/shapes.hpp"
#include <glm/ext.hpp>
#include <chicken3421/chicken3421.hpp>

namespace shapes {
    void calc_vertex_normals(mesh::mesh_template_t &mesh_template) {
        mesh_template.normals = std::vector<glm::vec3>(mesh_template.positions.size(), glm::vec3(0));
        chicken3421::expect(mesh_template.indices.size() != 0,
                            "shapes::calc_normals requires the mesh_template_t to have indices "
                            "defined");
        const auto &pos = mesh_template.positions;
        for (auto i = size_t{0}; i < mesh_template.indices.size() - 2; i += 3) {
            GLuint i1 = mesh_template.indices[i];
            GLuint i2 = mesh_template.indices[i + 1];
            GLuint i3 = mesh_template.indices[i + 2];
            auto a = pos[i2] - pos[i1];
            auto b = pos[i3] - pos[i1];
            auto face_normal = glm::normalize(glm::cross(a, b));
            mesh_template.normals[i1] += face_normal;
            mesh_template.normals[i2] += face_normal;
            mesh_template.normals[i3] += face_normal;
        }
        // normalise all the normals
        for (auto i = size_t{0}; i < mesh_template.normals.size(); ++i) {
            mesh_template.normals[i] = glm::normalize(mesh_template.normals[i]);
        }
    }

    // assumes the mesh_template does not have indices
    void calc_face_normals(mesh::mesh_template_t &mesh_template) {
        chicken3421::expect(mesh_template.indices.size() == 0,
                            "shapes::calc_face_normals requires the mesh_template to not use "
                            "indices");
        mesh_template.normals =
                std::vector<glm::vec3>(mesh_template.positions.size(), glm::vec3(1, 0, 0));
        const auto &pos = mesh_template.positions;
        for (auto i = size_t{0}; i < mesh_template.positions.size() - 2; i += 3) {
            auto a = pos[i + 1] - pos[i];
            auto b = pos[i + 2] - pos[i];
            auto face_normal = glm::normalize(glm::cross(a, b));
            for (auto j = size_t{0}; j < 3; ++j) {
                mesh_template.normals[i + j] = face_normal;
            }
        }
    }

    // Duplicates any attributes based on the indices provided
    mesh::mesh_template_t expand_indices(const mesh::mesh_template_t &mesh_template) {
        chicken3421::expect(mesh_template.indices.size() != 0,
                            "shapes::expand_indices requires the mesh_template to have indices to "
                            "expand");
        auto new_mesh_template = mesh::mesh_template_t{};
        for (auto i: mesh_template.indices) {
            new_mesh_template.positions.push_back(mesh_template.positions[i]);
            if (!mesh_template.colors.empty()) {
                new_mesh_template.colors.push_back(mesh_template.colors[i]);
            }
            if (!mesh_template.tex_coords.empty()) {
                new_mesh_template.tex_coords.push_back(mesh_template.tex_coords[i]);
            }
            if (!mesh_template.normals.empty()) {
                new_mesh_template.normals.push_back(mesh_template.normals[i]);
            }
        }
        return new_mesh_template;
    }

    mesh::mesh_template_t make_cube(float width) {
        mesh::mesh_template_t cube;
        float hw = width / 2;
        cube.positions = {
                // front square
                {-hw, hw,  hw}, // top-left 0
                {-hw, -hw, hw}, // bottom-left 1
                {hw,  -hw, hw}, // bottom-right 2
                {hw,  hw,  hw}, // top-right 3
                // back square
                {-hw, hw,  -hw}, // top-left 4
                {-hw, -hw, -hw}, // bottom-left 5
                {hw,  -hw, -hw}, // bottom-right 6
                {hw,  hw,  -hw}, // top-right 7
        };

        cube.indices = {
                // front
                0,
                1,
                2,
                2,
                3,
                0,
                // back
                4,
                7,
                6,
                6,
                5,
                4,
                // top
                4,
                0,
                3,
                3,
                7,
                4,
                // bottom
                5,
                6,
                2,
                2,
                1,
                5,
                // left
                0,
                4,
                5,
                5,
                1,
                0,
                // right
                3,
                2,
                6,
                6,
                7,
                3,
        };
        return cube;
    }

    mesh::mesh_template_t make_plane(int width, int height) {
        mesh::mesh_template_t mesh_template;
        float hw = (float) width / 2.0f;
        float hh = (float) height / 2.0f;
        for (auto i = size_t{0}; i <= width; ++i) {
            for (auto j = size_t{0}; j <= height; ++j) {
                mesh_template.positions.emplace_back(-hw + (float) i, -hh + (float) j, 0);
                mesh_template.tex_coords.emplace_back((float) i / width, (float) j / height);
            }
        }
        for (auto i = size_t{0}; i < width; ++i) {
            auto curr = i * (height + 1);
            auto next = (i + 1) * (height + 1);
            for (auto j = size_t{0}; j < height; ++j) {
                mesh_template.indices.push_back(curr + j);
                mesh_template.indices.push_back(next + j);
                mesh_template.indices.push_back(next + j + 1);
                mesh_template.indices.push_back(next + j + 1);
                mesh_template.indices.push_back(curr + j + 1);
                mesh_template.indices.push_back(curr + j);
            }
        }
        return mesh_template;
    }

    
    mesh::mesh_template_t make_ndc_cube() {
        mesh::mesh_template_t cube;
    }

} // namespace shapes
