#include <webgpu/webgpu.hpp>

namespace wgpu {

struct RAII_Buffer: public Buffer {
    RAII_Buffer(): Buffer() {}
    RAII_Buffer(wgpu::Device device, const BufferDescriptor& desc): Buffer(device.createBuffer(desc)) {}
    ~RAII_Buffer() {
        if (*this) {
            Buffer::destroy();
            Buffer::release();
        }
    }
    RAII_Buffer& operator=(const RAII_Buffer& other) = delete;
    RAII_Buffer(const RAII_Buffer& other) = delete;
    RAII_Buffer& operator=(RAII_Buffer&& other) {
        std::swap(*this, other);
        return *this;
    }
    RAII_Buffer(RAII_Buffer&& other) {
        *this = std::move(other);
        other = RAII_Buffer{};
    }
    // : Buffer(std::exchange(other, nullptr)) {}
};

}  //namespace wgpu

void test() {
    wgpu::Device device;
    wgpu::BufferDescriptor buffer_descriptor;
    wgpu::RAII_Buffer buffer(device, buffer_descriptor);
    wgpu::CommandEncoder command_encoder = {};
    command_encoder.copyBufferToBuffer(buffer, 0, buffer, 0, 0);

    {
        command_encoder.copyBufferToBuffer(buffer, 0, buffer, 0, 0);
    }
}
