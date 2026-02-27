#pragma once
#include <Arduino.h>

class TouchSys {
public:
    static bool iniciar();
    static bool lerTato(); 

private:
    static int consecutiveHits;
    static const int TOUCH_THRESHOLD_SAMPLES = 5; // Mantido aqui pois é lógica interna do módulo
};