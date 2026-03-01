#pragma once
#include "drivers/ServoDriver.h"

class MotionService
{
public:
    void init();

    // API de Intenção Pura (O Behavior só vai chamar isto)
    void lookLeft();
    void lookRight();
    void lookUp();
    void lookDown();
    void lookCenter();
    
    // Movimentos combinados (Coreografia simples, sem lógica de estado)
    void nod();    // Dizer "Sim"
    void shake();  // Dizer "Não"

    // Fallback caso o Behavior precise de um ângulo específico exato
    void setHeadPosition(uint16_t pan, uint16_t tilt);

private:
    ServoDriver _servoDriver;
    bool _isMoving; // Estado funcional do serviço
};