#pragma once
#include "Animation.h"

class ImpactAnimation : public Animation {
private:
    float impactIntensity = 0.0f;

public:
    void trigger(float intensity) { impactIntensity = intensity; }
    void update(EyeModel& model, float dt) override;
};