#pragma once
#include <stdint.h>
#include <stddef.h>

struct FrameBuffer {
    uint8_t* data;
    size_t length;
    uint16_t width;
    uint16_t height;
};

class CameraDriver
{
public:
    bool init(int xclk, int pclk, int vsync, int href, int* dataPins, int sda, int scl);
    FrameBuffer* captureFrame();
    void releaseFrame(FrameBuffer* fb);

private:
    bool _isInitialized;
    FrameBuffer _agnosticFb;
};