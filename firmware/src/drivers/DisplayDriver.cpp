#include "DisplayDriver.h"

void DisplayDriver::init() {
    _tft.init();
    
    // Rotação 1 ou 3 para modo paisagem (Se a tela for 240x320)
    // Se a sua tela for um quadrado perfeito de 240x240, pode apagar a linha abaixo
    _tft.setRotation(1); 
    
    _tft.setBrightness(128); // Define o brilho (0 a 255)
    _tft.fillScreen(0x0000); // Limpa a tela pintando de preto
}

lgfx::LGFX_Device* DisplayDriver::getLGFX() {
    return &_tft;
}