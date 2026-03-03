#include "SaccadeAnimation.h"
#include <Arduino.h>

void SaccadeAnimation::update(EyeModel& model, float dt) {
    timer += dt;

    if (timer >= nextInterval) {
        // Gera novos alvos aleatórios dentro de limites seguros
        targetX = random(-15, 16);
        targetY = random(-10, 8);
        nextInterval = random(500, 3000) / 1000.0f;
        timer = 0;
    }

    // Interpolação suave (Easing) para movimento natural
    model.currentSaccadeX += (targetX - model.currentSaccadeX) * (speed * dt);
    model.currentSaccadeY += (targetY - model.currentSaccadeY) * (speed * dt);
}