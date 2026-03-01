#include "LightsService.h"
#include "core/config/hardware_config.h"
#include <Arduino.h>

void LightsService::init() {
    _driver.init(Hardware::Sensors::PIN_LED_DATA, Hardware::Sensors::NUM_LEDS);
    _currentPattern = LedPattern::IDLE;
    _breathValue = 0;
}

void LightsService::update() {
    uint32_t now = millis();
    if (now - _lastUpdate < 30) return; // 33 FPS para animações suaves
    _lastUpdate = now;

    switch (_currentPattern) {
        case LedPattern::IDLE:
            // Efeito de "respiração" azul
            _breathValue += 2;
            _driver.setLedColor(0, 0, 0, _breathValue);
            _driver.setLedColor(1, 0, 0, _breathValue);
            break;
            
        case LedPattern::LOW_BATTERY:
            _driver.setLedColor(0, 255, 165, 0); // Laranja
            _driver.setLedColor(1, 255, 165, 0);
            break;
            
        case LedPattern::ERROR:
            // Piscar vermelho
            if ((now / 200) % 2) _driver.clear();
            else {
                _driver.setLedColor(0, 255, 0, 0);
                _driver.setLedColor(1, 255, 0, 0);
            }
            break;
    }
    _driver.show();
}

void LightsService::setPattern(LedPattern pattern) { _currentPattern = pattern; }