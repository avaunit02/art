#pragma once
#define WEBGPU_CPP_IMPLEMENTATION
#include <libassert/assert.hpp>
#include <webgpu/webgpu.hpp>

#include "engine/glfw.hh"
#include "glfw3webgpu.h"

struct webgpu_t {
    wgpu::Device device = {};
    wgpu::Queue queue = {};
    wgpu::Surface surface = {};
    std::unique_ptr<wgpu::ErrorCallback> error_callback;
    webgpu_t() {
        wgpu::InstanceDescriptor desc = {};
        wgpu::Instance instance = wgpu::createInstance(desc);
        if (!instance) {
            throw std::runtime_error("webgpu error: failed to initialise");
        }
        wgpu::RequestAdapterOptions adapter_options = {};
        wgpu::Adapter adapter = instance.requestAdapter(adapter_options);

        wgpu::DeviceDescriptor device_descriptor = {};
        device = adapter.requestDevice(device_descriptor);

        error_callback = device.setUncapturedErrorCallback([](wgpu::ErrorType type, char const* message) {
            std::cout << "webgpu uncaptured device error: type " << type;
            if (message) {
                std::cout << " (" << message << ")";
            }
            std::cout << std::endl;
        });

        queue = device.getQueue();

        surface = glfwGetWGPUSurface(instance, glfw.window);
        if (!surface) {
            throw std::runtime_error("webgpu x glfw error: glfwGetWGPUSurface failed");
        }

        wgpu::SurfaceCapabilities surface_capabilities = {};
        surface.getCapabilities(adapter, &surface_capabilities);
        wgpu::TextureFormat texture_format = surface_capabilities.formats[0];

        wgpu::SurfaceConfiguration surface_config = {};
        surface_config.width = 640;
        surface_config.height = 480;
        surface_config.usage = wgpu::TextureUsage::RenderAttachment;
        surface_config.format = texture_format;
        surface_config.device = device;
        surface_config.presentMode = wgpu::PresentMode::Fifo;
        surface_config.alphaMode = wgpu::CompositeAlphaMode::Auto;
        surface.configure(surface_config);
    }
    void draw() {
        wgpu::TextureView texture_view = {};
        {
            wgpu::SurfaceTexture surface_texture;
            surface.getCurrentTexture(&surface_texture);
            if (surface_texture.status != wgpu::SurfaceGetCurrentTextureStatus::Success) {
                throw std::runtime_error("webgpu error: getCurrentTexture failed");
            }
            wgpu::Texture texture = surface_texture.texture;

            wgpu::TextureViewDescriptor texture_view_descriptor;
            texture_view_descriptor.format = texture.getFormat();
            texture_view_descriptor.dimension = wgpu::TextureViewDimension::_2D;
            texture_view_descriptor.baseMipLevel = 0;
            texture_view_descriptor.mipLevelCount = 1;
            texture_view_descriptor.baseArrayLayer = 0;
            texture_view_descriptor.arrayLayerCount = 1;
            texture_view_descriptor.aspect = wgpu::TextureAspect::All;
            texture_view = texture.createView(texture_view_descriptor);
        }

        wgpu::RenderPassColorAttachment renderpass_color_attachment = {};
        renderpass_color_attachment.view = texture_view;
        renderpass_color_attachment.loadOp = wgpu::LoadOp::Clear;
        renderpass_color_attachment.storeOp = wgpu::StoreOp::Store;
        renderpass_color_attachment.clearValue = wgpu::Color{0.1, 0.1, 0.1, 1.0};
#ifndef WEBGPU_BACKEND_WGPU
        renderpass_color_attachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
#endif
        wgpu::RenderPassDescriptor renderpass_descriptor = {};
        renderpass_descriptor.colorAttachmentCount = 1;
        renderpass_descriptor.colorAttachments = &renderpass_color_attachment;

        wgpu::CommandEncoderDescriptor command_encoder_descriptor = {};
        wgpu::CommandEncoder command_encoder = device.createCommandEncoder(command_encoder_descriptor);
        wgpu::RenderPassEncoder renderpass = command_encoder.beginRenderPass(renderpass_descriptor);
        renderpass.end();

        wgpu::CommandBufferDescriptor command_buffer_descriptor = {};
        const std::vector<WGPUCommandBuffer> command_buffers = {command_encoder.finish(command_buffer_descriptor)};

        queue.submit(command_buffers);

        surface.present();

#if defined(WEBGPU_BACKEND_DAWN)
        device.tick();
#elif defined(WEBGPU_BACKEND_WGPU)
        device.poll(false);
#endif
    }
};
