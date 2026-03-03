#pragma once
#include <Arduino.h>
#include "../model/EyeModel.h"

class SaccadeAnimation {
private:
    float targetX = 0;
    float targetY = 0;
    unsigned long lastMoveTime = 0;
    unsigned long nextInterval = 1000;
    
    // Suavização: 0.1 é bem fluido, 0.4 é mais brusco.
    const float easing = 0.12f; 

public:
    void update(EyeModel& model, unsigned long currentTime);
    
    // Função para o "Susto": Força um olhar rápido para um ponto
    void lookAt(float x, float y);
};