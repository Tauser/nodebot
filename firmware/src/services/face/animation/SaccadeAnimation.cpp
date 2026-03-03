#include "SaccadeAnimation.h"

void SaccadeAnimation::update(EyeModel& model, unsigned long currentTime) {
    // 1. Inteligência de Movimento: Sorteia um novo ponto de interesse
    if (currentTime - lastMoveTime > nextInterval) {
        targetX = random(-28, 29); // Movimento horizontal
        targetY = random(-18, 19); // Movimento vertical
        
        lastMoveTime = currentTime;
        // Tempo que o robô fica "focado" antes de olhar para outro lado
        nextInterval = random(1200, 4500); 
    }

    // 2. Matemática do Olhar "Redondo" (Easing)
    // Calcula a distância que falta percorrer
    float dx = targetX - model.currentSaccadeX;
    float dy = targetY - model.currentSaccadeY;

    // Move apenas uma fração da distância a cada frame (gera desaceleração suave)
    model.currentSaccadeX += dx * easing;
    model.currentSaccadeY += dy * easing;
}

void SaccadeAnimation::lookAt(float x, float y) {
    targetX = x;
    targetY = y;
    // Reseta o timer para ele manter o foco no ponto do susto por um tempo
    lastMoveTime = millis();
    nextInterval = 2000; 
}