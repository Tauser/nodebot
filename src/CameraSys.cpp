#include "CameraSys.h"

camera_config_t CameraSys::configCamera;

bool CameraSys::iniciar() {
    configCamera.pin_pwdn = -1;
    configCamera.pin_reset = -1;
    configCamera.pin_xclk = 15;
    configCamera.pin_sscb_sda = 4;
    configCamera.pin_sscb_scl = 5;
    configCamera.pin_d7 = 16;
    configCamera.pin_d6 = 17;
    configCamera.pin_d5 = 18;
    configCamera.pin_d4 = 12;
    configCamera.pin_d3 = 10;
    configCamera.pin_d2 = 8;
    configCamera.pin_d1 = 9;
    configCamera.pin_d0 = 11;
    configCamera.pin_vsync = 6;
    configCamera.pin_href = 7;
    configCamera.pin_pclk = 13;

    configCamera.xclk_freq_hz = 20000000;
    configCamera.pixel_format = PIXFORMAT_JPEG; 
    
    // GESTÃO DE MEMÓRIA DE ELITE
    if (psramFound()) {
        configCamera.frame_size = FRAMESIZE_QVGA; // 320x240
        configCamera.jpeg_quality = 10;           
        configCamera.fb_count = 2;               
        configCamera.fb_location = CAMERA_FB_IN_PSRAM; // OBRIGATÓRIO: Isola a RAM interna
        configCamera.grab_mode = CAMERA_GRAB_LATEST;
    } else {
        Serial.println("[CRITICAL] CameraSys: PSRAM OPI não detetada!");
        return false;
    }

    esp_err_t err = esp_camera_init(&configCamera);
    if (err != ESP_OK) return false;

    // Tunning do Sensor
    sensor_t * s = esp_camera_sensor_get();
    s->set_vflip(s, 1);       // Ajusta orientação
    s->set_hmirror(s, 1);     // Efeito espelho
    s->set_whitebal(s, 1);    // Equilíbrio de brancos automático
    s->set_ae_level(s, 2);    // Nível de exposição para interiores
    
    Serial.println("[OK] CameraSys: Visão computacional pronta em PSRAM.");
    return true;
}

camera_fb_t* CameraSys::capturarFrame() {
    return esp_camera_fb_get();
}

void CameraSys::liberarFrame(camera_fb_t* fb) {
    if (fb) esp_camera_fb_return(fb);
}