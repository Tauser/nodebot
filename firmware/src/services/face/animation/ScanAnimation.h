#pragma once
#include "Animation.h"

class ScanAnimation : public Animation {
private:
    float targetX = 0, targetY = 0;
    float timer = 0;
    bool active = false;

public:
    void start() { active = true; }
    void stop() { active = false; }
    void update(EyeModel& model, float dt) override;
};