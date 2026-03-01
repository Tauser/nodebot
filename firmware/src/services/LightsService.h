#pragma once
#include "drivers/LightsDriver.h"

enum class LedPattern {
    IDLE,       // Pulsação lenta azul
    THINKING,   // Rotação rápida branca
    ERROR,      // Vermelho piscante
    HAPPY,      // Arco-íris ou Verde
    LOW_BATTERY // Laranja pulsante
};

class LightsService {
public:
    void init();
    void update();
    void setPattern(LedPattern pattern);

private:
    LedDriver _driver;
    LedPattern _currentPattern;
    uint32_t _lastUpdate;
    uint8_t _breathValue;
};