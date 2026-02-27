#pragma once
#include <Arduino.h>
#include "Config.h"

class Lights {
public:
    static bool iniciar();
    static void atualizar(SystemState state);

private:
    static unsigned long ultimoPisca;
    static bool estadoLed;
};