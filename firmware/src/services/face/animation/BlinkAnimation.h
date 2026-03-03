#pragma once
#include <Arduino.h>
#include "../model/EyeModel.h"

class BlinkAnimation {
private:
    unsigned long lastBlinkTime = 0;
    unsigned long stateTimer = 0;

public:
    void update(EyeModel& model, unsigned long currentTime) {
        if (model.currentExpression == Expression::SURPRISED) {
            model.blinkFactor = 1.0;
            return; // Surpreso não pisca
        }

        switch (model.blinkState) {
            case BlinkState::EYE_OPEN:
                if (currentTime - lastBlinkTime > model.blinkInterval) {
                    model.blinkState = BlinkState::EYE_CLOSING;
                    stateTimer = currentTime;
                }
                break;
            case BlinkState::EYE_CLOSING:
                model.blinkFactor = 0.1;
                if (currentTime - stateTimer > 30) { 
                    model.blinkState = BlinkState::EYE_CLOSED;
                    stateTimer = currentTime;
                }
                break;
            case BlinkState::EYE_CLOSED:
                if (currentTime - stateTimer > 80) {
                    model.blinkState = BlinkState::EYE_OPENING;
                    stateTimer = currentTime;
                }
                break;
            case BlinkState::EYE_OPENING:
                model.blinkFactor = 1.0;
                if (currentTime - stateTimer > 30) { 
                    model.blinkState = BlinkState::EYE_OPEN;
                    lastBlinkTime = currentTime;
                    model.blinkInterval = random(2000, 6000); 
                }
                break;
        }
    }
};