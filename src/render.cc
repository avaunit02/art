#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <random>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "util/profiler.hh"

#include "engine/glerror.hh"
#include "engine/glfw.hh"
#include "engine/shared-uniforms.hh"

#include "scenes/noise-flow-particles.hh"
#include "scenes/brain.hh"
#include "scenes/wanikani-subject-grid.hh"
#include "scenes/wanikani-review-time-grid.hh"
#include "scenes/grid-bezier.hh"
#include "scenes/scratch.hh"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfw_t glfw;

    glfwSetInputMode(glfw.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(glfw.window, GLFW_STICKY_KEYS, 1);
    glfwSetKeyCallback(glfw.window, key_callback);

    gl_setup_errors();

    shared_uniforms shared{glfw};

    //brain scene{glfw, true};
    //noise_flow_particles scene{glfw};
    //wanikani_subject_grid scene{glfw};
    //wanikani_review_time_grid scene{glfw};
    //grid_bezier scene{glfw};
    scratch scene{glfw};

    glfwSetTime(0);
    while (!glfwWindowShouldClose(glfw.window)) {
        scene.draw();
        glfw.draw();
    }

    std::cout << scene.shared.inputs.time * scene.shared.inputs.framerate / glfwGetTime() << " average fps" << std::endl;
}
