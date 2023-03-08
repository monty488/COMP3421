#include <glm/glm.hpp>

struct directional_light_t {
    glm::vec3 ambient;
    glm::vec3 diffuse;
};

struct point_light_t {
    // TODO: change fields
    glm::vec3 pos;
    glm::vec3 color;
};

