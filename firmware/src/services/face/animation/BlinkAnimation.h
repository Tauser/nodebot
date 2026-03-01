#pragma once
#include "Animation.h"
#include "../model/EyeModel.h"
#include <math.h>

class BlinkAnimation : public Animation {
private:
    EyeModel* _model = nullptr;
    uint32_t _elapsed = 0;
    const uint32_t _duration = 220; // ms

public:
    void attachModel(EyeModel* m) { _model = m; }

    void start() override { _elapsed = 0; }

    void update(uint32_t deltaMs) override {
        if (!_model) return;
        _elapsed += deltaMs;
        
        float t = (float)_elapsed / _duration;
        if (t > 1.0f) t = 1.0f;

        // Easing curve (Parábola)
        float curve = (t < 0.5f) ? (2.0f * t * t) : (1.0f - pow(-2.0f * t + 2.0f, 2.0f) / 2.0f);
        _model->setLid(1.0f - curve);
    }

    bool finished() override { return _elapsed >= _duration; }
    int priority() const override { return 2; }
};