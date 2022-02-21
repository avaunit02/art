#include "engine/drawable.hh"
#include "engine/shader.hh"
#include "engine/shared-uniforms.hh"

struct template_scene {
    shared_uniforms& shared;

    template_scene(shared_uniforms& shared_):
        shared{shared_},
    {
    }
    void draw() {
    }
};
