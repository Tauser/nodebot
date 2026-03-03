#pragma once
#include "LGFX_Config.h" // Puxa todas as configurações de pinos e do ST7789

class DisplayDriver {
private:
    LGFX _tft; // Instancia o display com base no seu LGFX_Config

public:
    void init();
    lgfx::LGFX_Device* getLGFX(); // Retorna o ponteiro para o motor de rosto usar
};