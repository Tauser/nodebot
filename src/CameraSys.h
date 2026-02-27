#pragma once
#include <Arduino.h>
#include "esp_camera.h"

class CameraSys {
public:
    static bool iniciar();
    
    static camera_fb_t* capturarFrame(); 
    static void liberarFrame(camera_fb_t* fb);

private:
    static camera_config_t configCamera;
};