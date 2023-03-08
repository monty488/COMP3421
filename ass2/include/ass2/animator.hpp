#ifndef COMP3421_TUTORIAL_05_ANIMATOR_HPP
#define COMP3421_TUTORIAL_05_ANIMATOR_HPP

#include <glm/ext.hpp>

#include <ass2/scene.hpp>

/**
 * A bezier curve consisting of 2 segments.
 * s1 and s2 are vectors of 4 control points each.
 * The end of s1 and start of s2 are the same.
 * The end of s2 and start of s1 are the same.
 * In this way, a closed-loop is formed smoothly.
 */
struct bspline_t {
    std::vector<glm::vec3> s1;
    std::vector<glm::vec3> s2;
};

/**
 * A type representing a figure-8, or lemniscate.
 * Unremarkable.
 */
struct lemniscate_t {};
struct small_lemniscate_t {};
/**
 * Our primitive animator only can draw lemniscates.
 *
 */
struct animator_t {
    bspline_t spline_animation;
    lemniscate_t lemniscate_animation;
    small_lemniscate_t small_lemi_animation;
};

/**
 * Given the current animation context animator and time, apply animations to the scene.
 *
 * Currently, the only two animations applied are figure-8s.
 *
 * @param animator The animation context
 * @param scene The scene to animate
 * @param now The current time in seconds.
 */
void animate(const animator_t &animator, scene_t &scene, float now);

/**
 * Initialise the animation context
 * @return A fresh animator
 */
animator_t make_animator();

#endif //COMP3421_TUTORIAL_05_ANIMATOR_HPP
