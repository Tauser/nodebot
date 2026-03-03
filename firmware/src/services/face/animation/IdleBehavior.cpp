#include "IdleBehavior.h"

void IdleBehavior::update(EyeModel& model, float dt) {
    unsigned long now = millis();
    if (now - lastActivityTime > 15000) { // 15s sem comandos
        eventTimer += dt;
        if (eventTimer > 5.0f) {
            // Alterna entre tédio e sono
            model.currentExpression = (random(0, 2) == 0) ? 
                                       Expression::UNIMPRESSED : Expression::SQUINT;
            eventTimer = 0;
        }
    }
}