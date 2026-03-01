#pragma once
#include "Animation.h"
#include "../model/EyeModel.h"

class EmotionTransition : public Animation {
private:
    EyeModel* _model = nullptr;
    float _startSize;
    float _targetSize;
    uint32_t _elapsed = 0;
    const uint32_t _duration = 400;

public:
    void attachModel(EyeModel* m) { _model = m; }

    void setTargetSize(float target) { _targetSize = target; }

    void start() override {
        if (!_model) return;
        _startSize = _model->get().pupilSize;
        _elapsed = 0;
    }

    void update(uint32_t deltaMs) override {
        if (!_model) return;
        _elapsed += deltaMs;
        
        float t = (float)_elapsed / _duration;
        if (t > 1.0f) t = 1.0f;

        float smooth = t * t * (3.0f - 2.0f * t); // Smoothstep

        float size = _startSize + (_targetSize - _startSize) * smooth;
        _model->setPupilSize(size);
    }

    bool finished() override { return _elapsed >= _duration; }
    int priority() const override { return 1; }
};