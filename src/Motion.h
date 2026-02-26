#pragma once
#include <Arduino.h>
#include <SCServo.h> // A biblioteca que vamos baixar para a pasta lib
#include "../include/Config.h"

class Motion {
public:
    static void iniciar();
    static void olharPara(int pan, int tilt); // Movimento coordenado
    static void centralizar();
    static void relaxar(); // Desliga o torque para economizar energia/calor

private:
    static SMS_STS st; // Objeto de controle da Feetech (SCS Series)
};