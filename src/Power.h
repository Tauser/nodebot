#pragma once
#include <Arduino.h>

class Power {
public:
    static bool iniciar();
    static void monitorar();

private:
    static float lerVoltagem();
    static const float VOLTAGEM_MINIMA; 
};