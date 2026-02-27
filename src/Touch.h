#pragma once
#include <Arduino.h>

class TouchSys {
public:
    static bool iniciar();
    static bool lerTato(); // Retorna true se alguém estiver a fazer carinho

private:
    static const int PINO_FITA_COBRE = 4; // Ajuste no Config.h depois
    static const int LIMIAR_TATO = 30000; // No ESP32-S3 os valores capacitivos são altos
    static bool isTocado;
};
