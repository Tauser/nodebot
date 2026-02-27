#pragma once
#include <Arduino.h>

class TouchSys {
public:
    static bool iniciar();
    static bool lerTato(); 

private:
    static const int PINO_FITA_COBRE = 4; // Ajuste para o seu pino
    static const int LIMIAR_CAPACITIVO = 30000;
    static int consecutiveHits;
    static const int TOUCH_THRESHOLD_SAMPLES = 5; 
};