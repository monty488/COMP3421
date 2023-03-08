#include <ass2/scene.hpp>

const char* CLOUD_PATH = "res/obj/Cloud/Cloud_Piece.obj";
const char* SEPHIROTH_PATH = "res/obj/Sephiroth/Sephiroth_Piece.obj";
const char* YOJIMBO_PATH = "res/obj/Yojimbo/Yojimbo.obj";
const char* PLANE_PATH = "res/obj/scene/plane.obj";
const char* LIGHT_SPHERE_PATH = "res/obj/light_mesh/light_mesh.obj";

scene_t make_scene() {
    camera_t free_cam = make_freeroam_camera({ 20, 20, -5 }, { 0, 0, 0 }); 
    camera_t player_cam = make_player_camera({ 20, 4, -5 }, { 0, 0, 0 }); 


    node_t light_sphere = {
        node_t::LIGHT_SPHERE,
        load_obj(LIGHT_SPHERE_PATH, {glm::vec3(1, 1, 1), glm::vec3(0,0,0), glm::vec3(0.0, 2.0, 0.0), 2}),
        glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)),
        { }
    };

    node_t light_sphere_2 = {
        node_t::LIGHT_SPHERE_2,
        load_obj(LIGHT_SPHERE_PATH, {glm::vec3(1, 1, 1), glm::vec3(0,0,0), glm::vec3(1.0, 0.0, 3.0), 2}),
        glm::mat4(1),
        { }
    };

    node_t cloud = {
        node_t::CLOUD,
        load_obj(CLOUD_PATH, {glm::vec3(1, 1, 1), glm::vec3(0,0,0), glm::vec3(0,0,0), 2}),
        glm::scale(glm::mat4(1), glm::vec3(5)),
        { light_sphere }
    };
 
    node_t sephiroth = {
        node_t::CLOUD,
        load_obj(SEPHIROTH_PATH, {glm::vec3(1, 1, 1), glm::vec3(0,0,0), glm::vec3(0,0,0), 2}),
        glm::translate(glm::mat4(1), glm::vec3(0, 0, 10)) * glm::scale(glm::mat4(1), glm::vec3(5)) * glm::rotate(glm::mat4(1), 360.5f, glm::vec3(0.0, 1.0, 0.0)),
        { light_sphere_2 }
    };

    node_t plane = {
        node_t::PLANE,
        load_obj(PLANE_PATH, {glm::vec3(1,1,1), glm::vec3(0.5,0.5,0.5), glm::vec3(0,0,0), 2}),
        glm::mat4(1),
        { cloud, sephiroth }
    };

    point_light_t light_1 = {
        glm::vec3{ 0, 4, 0 },
        glm::vec3{ 0.0, 2.0, 0.0 }
    };


    point_light_t light_2 = {
        glm::vec3{ 0, 4, 7 },
        glm::vec3{ 1.0, 0.0, 3.0 }
    };

    return scene_t{ free_cam, free_cam, plane, light_1, light_2, player_cam };
}