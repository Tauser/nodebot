#pragma once
#include "Animation.h"

class BootAnimation : public Animation {
private:
    float timer = 0;
    bool finished = false;

public:
    bool isFinished() const { return finished; }

    void update(EyeModel& model, float dt) override {
        if (finished) return;
        timer += dt;

        if (timer < 0.8f) { // Olho esquerdo acende
            model.blinkFactor = (sin(timer * 25.0f) > 0) ? 0.4f : 0.0f;
            model.rightScaleY = 0;
        } else if (timer < 1.5f) { // Olho direito acende
            model.blinkFactor = 1.0f;
            model.rightScaleY = (timer - 0.8f) * 1.3f;
        } else if (timer < 2.5f) { // Zoom de "foco"
            float zoom = 1.0f + sin((timer - 1.5f) * PI) * 0.2f;
            model.leftScaleY = model.rightScaleY = zoom;
        } else {
            model.leftScaleY = model.rightScaleY = 1.0f;
            finished = true;
        }
    }
};