#pragma once
#include <Arduino.h>
#include "../model/EyeModel.h"
#include "BlinkAnimation.h"
#include "SaccadeAnimation.h"

class AnimationEngine {
private:
    BlinkAnimation blinkAnim;
    SaccadeAnimation saccadeAnim;

public:
    // O loop principal continua chamando o update automático
    void update(EyeModel& model) { 
    unsigned long currentTime = millis();

    blinkAnim.update(model, currentTime);
    saccadeAnim.update(model, currentTime);

    // --- Lógica de Irregularidade Humana ---
    static unsigned long lastChange = 0;
    if (currentTime - lastChange > 3000) { // Muda o "humor" a cada 3 segundos
        // Sorteia uma leve diferença (entre 95% e 105% do tamanho original)
        model.targetLeftScaleY = random(95, 106) / 100.0f;
        model.targetRightScaleY = random(95, 106) / 100.0f;
        lastChange = currentTime;
    }

    // Suaviza a transição (Easing)
    model.leftScaleY += (model.targetLeftScaleY - model.leftScaleY) * 0.4f;
    model.rightScaleY += (model.targetRightScaleY - model.rightScaleY) * 0.4f;
}
};