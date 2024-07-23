#pragma once

#include <utility>
#include <vector>
#include <webgpu/webgpu.hpp>

#include "util/gl-data-layout.hh"

enum class BufferType {
    vertex,
    index,
    uniform,
    storage,
};

template <BufferType buffer_type>
wgpu::BufferUsage type_to_buffer_usage() {
    if constexpr (buffer_type == BufferType::vertex) {
        return wgpu::BufferUsage::Vertex;
    } else if constexpr (buffer_type == BufferType::index) {
        return wgpu::BufferUsage::Index;
    } else if constexpr (buffer_type == BufferType::uniform) {
        return wgpu::BufferUsage::Uniform;
    } else if constexpr (buffer_type == BufferType::storage) {
        return wgpu::BufferUsage::Storage;
    }
}

template <typename T>
wgpu::IndexFormat type_to_index_format() {
    if constexpr (false) {
    } else if constexpr (std::is_same_v<uint16_t, T>) {
        return wgpu::IndexFormat::Uint16;
    } else if constexpr (std::is_same_v<uint32_t, T>) {
        return wgpu::IndexFormat::Uint32;
    } else {
        static_assert(false, "unsupported type in type_to_index_format");
    }
}

template <typename T>
std::string type_to_shader_text_type() {
    if constexpr (false) {
    } else if constexpr (std::is_same_v<float, T>) {
        return "f32";
    } else if constexpr (std::is_same_v<std::array<float, 2>, T>) {
        return "vec2<f32>";
    } else if constexpr (std::is_same_v<std::array<float, 3>, T>) {
        return "vec3<f32>";
    } else if constexpr (std::is_same_v<std::array<float, 4>, T>) {
        return "vec4<f32>";
    } else if constexpr (std::is_same_v<std::array<uint8_t, 2>, T>) {
        return "vec2<u8>";
    } else if constexpr (std::is_same_v<std::array<uint8_t, 4>, T>) {
        return "vec4<u8>";
    } else if constexpr (std::is_same_v<std::array<int8_t, 2>, T>) {
        return "vec2<i8>";
    } else if constexpr (std::is_same_v<std::array<int8_t, 4>, T>) {
        return "vec4<i8>";
    } else if constexpr (std::is_same_v<std::array<uint16_t, 2>, T>) {
        return "vec2<u16>";
    } else if constexpr (std::is_same_v<std::array<uint16_t, 4>, T>) {
        return "vec4<u16>";
    } else if constexpr (std::is_same_v<std::array<int16_t, 2>, T>) {
        return "vec2<i16>";
    } else if constexpr (std::is_same_v<std::array<int16_t, 4>, T>) {
        return "vec4<i16>";
    } else if constexpr (std::is_same_v<uint32_t, T>) {
        return "u32";
    } else if constexpr (std::is_same_v<std::array<uint32_t, 2>, T>) {
        return "vec2<u32>";
    } else if constexpr (std::is_same_v<std::array<uint32_t, 3>, T>) {
        return "vec3<u32>";
    } else if constexpr (std::is_same_v<std::array<uint32_t, 4>, T>) {
        return "vec4<u32>";
    } else if constexpr (std::is_same_v<int32_t, T>) {
        return "s32";
    } else if constexpr (std::is_same_v<std::array<int32_t, 2>, T>) {
        return "vec2<s32>";
    } else if constexpr (std::is_same_v<std::array<int32_t, 3>, T>) {
        return "vec3<s32>";
    } else if constexpr (std::is_same_v<std::array<int32_t, 4>, T>) {
        return "vec4<s32>";
    } else {
        static_assert(false, "unsupported type in type_to_shader_text_type");
    }
    // NOTE *norm* and Float16 aren't supported i.e.:
    // Undefined
    // Unorm8x2 Unorm8x4 Snorm8x2 Snorm8x4
    // Unorm16x2 Unorm16x4 Snorm16x2 Snorm16x4
    // Float16x2 Float16x4
    // Unorm10_10_10_2
}

template <typename T>
wgpu::VertexFormat type_to_vertex_format() {
    if constexpr (false) {
    } else if constexpr (std::is_same_v<float, T>) {
        return wgpu::VertexFormat::Float32;
    } else if constexpr (std::is_same_v<std::array<float, 2>, T>) {
        return wgpu::VertexFormat::Float32x2;
    } else if constexpr (std::is_same_v<std::array<float, 3>, T>) {
        return wgpu::VertexFormat::Float32x3;
    } else if constexpr (std::is_same_v<std::array<float, 4>, T>) {
        return wgpu::VertexFormat::Float32x4;
    } else if constexpr (std::is_same_v<std::array<uint8_t, 2>, T>) {
        return wgpu::VertexFormat::Uint8x2;
    } else if constexpr (std::is_same_v<std::array<uint8_t, 4>, T>) {
        return wgpu::VertexFormat::Uint8x4;
    } else if constexpr (std::is_same_v<std::array<int8_t, 2>, T>) {
        return wgpu::VertexFormat::Sint8x2;
    } else if constexpr (std::is_same_v<std::array<int8_t, 4>, T>) {
        return wgpu::VertexFormat::Sint8x4;
    } else if constexpr (std::is_same_v<std::array<uint16_t, 2>, T>) {
        return wgpu::VertexFormat::Uint16x2;
    } else if constexpr (std::is_same_v<std::array<uint16_t, 4>, T>) {
        return wgpu::VertexFormat::Uint16x4;
    } else if constexpr (std::is_same_v<std::array<int16_t, 2>, T>) {
        return wgpu::VertexFormat::Sint16x2;
    } else if constexpr (std::is_same_v<std::array<int16_t, 4>, T>) {
        return wgpu::VertexFormat::Sint16x4;
    } else if constexpr (std::is_same_v<uint32_t, T>) {
        return wgpu::VertexFormat::Uint32;
    } else if constexpr (std::is_same_v<std::array<uint32_t, 2>, T>) {
        return wgpu::VertexFormat::Uint32x2;
    } else if constexpr (std::is_same_v<std::array<uint32_t, 3>, T>) {
        return wgpu::VertexFormat::Uint32x3;
    } else if constexpr (std::is_same_v<std::array<uint32_t, 4>, T>) {
        return wgpu::VertexFormat::Uint32x4;
    } else if constexpr (std::is_same_v<int32_t, T>) {
        return wgpu::VertexFormat::Sint32;
    } else if constexpr (std::is_same_v<std::array<int32_t, 2>, T>) {
        return wgpu::VertexFormat::Sint32x2;
    } else if constexpr (std::is_same_v<std::array<int32_t, 3>, T>) {
        return wgpu::VertexFormat::Sint32x3;
    } else if constexpr (std::is_same_v<std::array<int32_t, 4>, T>) {
        return wgpu::VertexFormat::Sint32x4;
    } else {
        static_assert(false, "unsupported type in type_to_vertex_format");
    }
    // NOTE *norm* and Float16 aren't supported i.e.:
    // Undefined
    // Unorm8x2 Unorm8x4 Snorm8x2 Snorm8x4
    // Unorm16x2 Unorm16x4 Snorm16x2 Snorm16x4
    // Float16x2 Float16x4
    // Unorm10_10_10_2
}

template <typename T, BufferType buffer_type>
struct buffer {
    wgpu::BufferUsage usage;
    wgpu::Buffer buffer;
    size_t attribute_location

    buffer() = delete;
    buffer(std::vector<T> data, wgpu::BufferUsage usage_ = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc):
        usage(usage_) {
        usage |= type_to_buffer_usage<BufferType>();
        wgpu::BufferDescriptor buffer_descriptor;
        buffer_descriptor.usage = usage;
        buffer_descriptor.size = data.size() * sizeof(T);
        buffer_descriptor.mappedAtCreation = false;
        buffer = device.createBuffer(buffer_descriptor);
        queue.writeBuffer(buffer, 0, data.size(), data.size() * sizeof(T));
    }

    std::string shader_text(std::string name) {
        return std::format("@location({}) {}: {}", location, name, type_to_shader_text_type<T>());
    }

    template <typename D>
    void bind(wgpu::RenderPass renderpass, wgpu::Pipeline pipeline, size_t location, D d) {
        if constexpr (buffer_type == BufferType::vertex) {
            wgpu::VertexAttribute attribute;
            attribute.shaderLocation = attribute_location;
            attribute.format = type_to_vertex_format<T>();
            attribute.offset = 0;

            wgpu::VertexBufferLayout vertex_buffer_layout;
            vertex_buffer_layout.attributeCount = 1;
            vertex_buffer_layout.attributes = &attribute;
            vertex_buffer_layout.arrayStride = sizeof(T);
            vertex_buffer_layout.stepMode = wgpu::VertexStepMode::Vertex;
            //TODO wgpu::VertexStepMode::Instance for instancing
            //to have multiple vertices share the same record

            pipeline_descriptor.vertex.bufferCount = 1;
            pipeline_descriptor.vertex.buffers = &vertex_buffer_layout;

            renderpass.setPipeline(pipeline);
            renderpass.setVertexBuffer(0, buffer, 0, buffer.getSize());
            renderpass.draw(data.size(), 1, 0, 0);
        } else if constexpr (buffer_type == BufferType::index) {
            renderpass.setIndexBuffer();
        } else if constexpr (buffer_type == BufferType::uniform) {
        } else if constexpr (buffer_type == BufferType::storage) {
        }
    }

    void bind(wgpu::RenderPass renderpass, wgpu::Pipeline pipeline, size_t location) { bind(program, location, T{}); }

    ~buffer() {
        buffer.destroy();
        buffer.release();
    }
};

template <typename T>
using vertex_buffer = buffer<T, BufferType::vertex>;
template <typename T>
using index_buffer = buffer<T, BufferType::index>;
template <typename T>
using uniform_buffer = buffer<T, BufferType::uniform>;
template <typename T>
using storage_buffer = buffer<T, BufferType::storage>;
