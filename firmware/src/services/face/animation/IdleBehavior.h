#pragma once
#include "Animation.h"
#include <Arduino.h>

class IdleBehavior : public Animation {
private:
    unsigned long lastActivityTime = 0;
    float eventTimer = 0;
    bool isIdle = false;

public:
    void resetActivity() {
        lastActivityTime = millis();
        isIdle = false;
    }

    void update(EyeModel& model, float dt) override;
};