#ifndef COMP3421_SHAPES_HPP
#define COMP3421_SHAPES_HPP

#include <glm/glm.hpp>
#include "ass3/mesh.hpp"

namespace shapes {

    mesh::mesh_template_t make_cube(float width);

    mesh::mesh_template_t make_plane(int width, int height);


    // assumes the mesh_template has indices
    void calc_vertex_normals(mesh::mesh_template_t &mesh_template);

    // assumes the mesh_template does not have indices
    void calc_face_normals(mesh::mesh_template_t &mesh_template);

    // duplicates any attributes based on the indices provided
    mesh::mesh_template_t expand_indices(const mesh::mesh_template_t &mesh_template);

} // namespace shapes
#endif // COMP3421_SHAPES_HPP
