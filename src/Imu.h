#pragma once
#include <Arduino.h>

class ImuSys {
public:
    static bool iniciar();
    static void atualizar();
    static bool isAgitado();
    static bool isCaido();
};