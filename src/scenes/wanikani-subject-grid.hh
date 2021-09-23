#include "engine/buffers.hh"
#include "engine/shader.hh"
#include "engine/shared-uniforms.hh"

struct wanikani_subject_grid {
    glfw_t& glfw;
    shared_uniforms shared;

    monospace_unicode_font_atlas atlas;
    text_wanikani text;
    json j;

    wanikani_subject_grid(glfw_t& glfw_):
        glfw{glfw_},
        shared{glfw},
        atlas{"fonts/unifont-13.0.06.pcf"},
        text{shared, atlas}
    {
        std::ifstream i("data/wanikani/data.json");
        i >> j;
    }
    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int w, h;
        glfwGetWindowSize(glfw.window, &w, &h);
        float w_ = w;
        float h_ = h;
        shared.inputs.projection = glm::ortho(0.0f, w_, 0.0f, h_, 0.0f, 200.0f);
        shared.inputs.view = glm::identity<glm::mat4>();
        shared.draw();

        {
            text.drawable.vbo.data.clear();
            text.extra_buffer.data.clear();
            size_t s = 24;
            size_t rows = h / s;
            size_t i = 0;
            float start_timestamp = j["start_timestamp"];
            float end_timestamp = j["end_timestamp"];
            for (json::iterator it = j["subjects"].begin(); it != j["subjects"].end(); ++it, i++) {
                float x = floor(i / rows) * s;
                float y = floor(i % rows) * s;
                std::string character = (*it)["character"];
                auto& updates = (*it)["updates"];
                float timestamp = std::numeric_limits<float>::infinity();
                uint32_t stage = 1;
                for (json::iterator jt = updates.begin(); jt != updates.end(); ++jt) {
                    float next_timestamp = (*jt)["data_updated_at"];
                    next_timestamp = (next_timestamp - start_timestamp) / (end_timestamp - start_timestamp) * 100;
                    if (shared.inputs.time > next_timestamp) {
                        timestamp = next_timestamp;
                        stage = (*jt)["ending_srs_stage"];
                    } else {
                        break;
                    }
                }
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                std::wstring wide = converter.from_bytes(character);
                text.gen_text(wide, {x, y});
                for (size_t i = 0; i < 6; i++) {
                    text.extra_buffer.data.push_back({timestamp, stage});
                }
            }
        }
        text.draw();
    }
};
