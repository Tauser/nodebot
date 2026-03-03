#pragma once
#include "Animation.h"

class SaccadeAnimation : public Animation {
public:
    void update(EyeModel& model, float dt) override;

private:
    float targetX = 0, targetY = 0;
    float timer = 0;
    float nextInterval = 1.0f;
    float speed = 12.0f;
};