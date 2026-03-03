#include "ScanAnimation.h"
#include <Arduino.h>

void ScanAnimation::update(EyeModel& model, float dt) {
    if (!active) return;

    timer += dt;
    if (timer > 0.25f) { // Muda o alvo rapidamente
        targetX = random(-70, 71); 
        targetY = random(-90, 30);
        timer = 0;
    }

    // Movimento brusco e rápido
    float moveSpeed = 25.0f;
    model.currentSaccadeX += (targetX - model.currentSaccadeX) * (moveSpeed * dt);
    model.currentSaccadeY += (targetY - model.currentSaccadeY) * (moveSpeed * dt);
    
    // Força uma expressão de desconfiança durante o scan
    model.currentExpression = Expression::SUSPICIOUS;
}