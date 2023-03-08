#ifndef COMP3421_TUTORIAL_05_MODEL_HPP
#define COMP3421_TUTORIAL_05_MODEL_HPP

#include <vector>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

/**
 * A struct that represents the raw geometry of a model.
 * Does not contain all the usual graphics things, yet.
 */
struct mesh_t {
    GLuint vao;
    GLuint vbo;
    GLuint nverts;
    int material_id;
};

/**
 * A struct that represents what a mesh is "made out of"
 * This can be colours, textures, and even more...
 */
struct material_t {
    GLuint diff_map;
    GLuint spec_map;
    glm::vec4 color;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    float shininess;
};

struct material_param_t {
    glm::vec3 diffuse = glm::vec3(1, 1, 1);
    glm::vec3 specular = glm::vec3(1, 1, 1);
    glm::vec3 emissive = glm::vec3(0, 0, 0);
    float shininess = 10;
};


/**
 * A representation of a model loaded from an artist's tool
 */
struct model_t {
    std::vector<mesh_t> meshes;
    std::vector<material_t> materials;
};

/**
 * Load a model from the .obj format
 *
 * @param path The path to the model's .obj file
 * @return A freshly initialised model, with everything uploaded to the GPU already
 */
model_t load_obj(const std::string &path, material_param_t mat_params);

/**
 * Destroy a model, freeing all of its GPU resources
 * @param m The model to destroy
 */
void destroy_obj(model_t &m);

#endif //COMP3421_TUTORIAL_05_MODEL_HPP
