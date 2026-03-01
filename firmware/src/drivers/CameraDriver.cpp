#include "CameraDriver.h"
#include "esp_camera.h"

static camera_fb_t* _internalFb = nullptr;

bool CameraDriver::init(int xclk, int pclk, int vsync, int href, int* dataPins, int sda, int scl)
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    
    config.pin_d0 = dataPins[0];
    config.pin_d1 = dataPins[1];
    config.pin_d2 = dataPins[2];
    config.pin_d3 = dataPins[3];
    config.pin_d4 = dataPins[4];
    config.pin_d5 = dataPins[5];
    config.pin_d6 = dataPins[6];
    config.pin_d7 = dataPins[7];
    
    config.pin_xclk = xclk;
    config.pin_pclk = pclk;
    config.pin_vsync = vsync;
    config.pin_href = href;
    config.pin_sccb_sda = sda;
    config.pin_sccb_scl = scl;
    config.pin_pwdn = -1;
    config.pin_reset = -1;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    esp_err_t err = esp_camera_init(&config);
    _isInitialized = (err == ESP_OK);
    return _isInitialized;
}

FrameBuffer* CameraDriver::captureFrame()
{
    if (!_isInitialized) return nullptr;
    
    _internalFb = esp_camera_fb_get();
    if (!_internalFb) return nullptr;

    _agnosticFb.data = _internalFb->buf;
    _agnosticFb.length = _internalFb->len;
    _agnosticFb.width = _internalFb->width;
    _agnosticFb.height = _internalFb->height;
    
    return &_agnosticFb;
}

void CameraDriver::releaseFrame(FrameBuffer* fb)
{
    if (_internalFb) {
        esp_camera_fb_return(_internalFb);
        _internalFb = nullptr;
    }
}