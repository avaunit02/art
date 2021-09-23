#include "engine/drawable.hh"
#include "engine/shader.hh"
#include "engine/shared-uniforms.hh"
#include "drawables/grid-bezier-evaluator.hh"

struct grid_bezier {
    glfw_t& glfw;
    shared_uniforms shared;
    grid_bezier_evaluator<2, glm::vec3> gbe;

    grid_bezier(glfw_t& glfw_):
        glfw{glfw_},
        shared{glfw},
        gbe{shared, GL_POINT, 32, 32}
    {
        gbe.controls = {
            glm::vec3{0, 0, -10},
            glm::vec3{5, 5, -5},
            glm::vec3{10, 0, -10},

            glm::vec3{0, 5, -5},
            glm::vec3{5, 5, -5},
            glm::vec3{10, 5, -5},

            glm::vec3{0, 10, -10},
            glm::vec3{5, 5, -5},
            glm::vec3{10, 10, -10},
        };
    }
    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int w, h;
        glfwGetWindowSize(glfw.window, &w, &h);
        shared.inputs.projection = glm::perspective(glm::radians(75.0f), static_cast<float>(w) / h, 0.1f, 200.f);
        shared.inputs.view = glm::lookAt(
            glm::vec3(0, 0, 20),
            glm::vec3(0, 0, -10),
            glm::vec3(0, 1, 0)
        );
        shared.draw();

        gbe.draw();
    }
};
