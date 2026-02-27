#pragma once
#include <Arduino.h>
#include "esp_camera.h"

class CameraSys {
public:
    static bool iniciar();
    static void tirarFotoSalvarSD(const char* caminhoFicheiro);
};