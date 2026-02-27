#pragma once
#include <Arduino.h>
#include <SCServo.h>
#include "../include/Config.h"

class Motion {
public:
    static bool iniciar();
    static void atualizar(SystemState estadoAtual); 
    static void olharPara(int pan, int tilt, int vel = 500, int acc = 50);
    static void relaxar();
    static void centralizar();


    // Safe Zones
    static const int PAN_MIN = 1024;
    static const int PAN_MAX = 3072;
    static const int TILT_MIN = 1500;
    static const int TILT_MAX = 2500;

    private:
    static int alvoX;
    static int alvoY;

private:
    static SMS_STS st;
    static bool testarComunicacao();
};