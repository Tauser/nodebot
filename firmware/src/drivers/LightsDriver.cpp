#include "LightsDriver.h"

void LedDriver::init(int pin, int numLeds) {
    _numLeds = numLeds;
    _leds = new CRGB[_numLeds];
    
    // Inicialização dinâmica do FastLED baseada no pino do hardware_config
    // Nota: O pino precisa ser uma constante de compilação para o template do FastLED,
    // ou usamos a implementação de runtime se a biblioteca suportar.
    FastLED.addLeds<WS2812B, 2, GRB>(_leds, _numLeds); 
    FastLED.setBrightness(50); // Brilho moderado para poupar bateria
}

void LedDriver::setLedColor(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < _numLeds) {
        _leds[index] = CRGB(r, g, b);
    }
}

void LedDriver::show() { FastLED.show(); }
void LedDriver::clear() { FastLED.clear(); show(); }