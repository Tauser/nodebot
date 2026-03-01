#pragma once
#include "Animation.h"
#include "../model/EyeModel.h"

class SaccadeAnimation : public Animation {
private:
    EyeModel* _model = nullptr;
    float _startX, _startY;
    float _targetX, _targetY;
    uint32_t _elapsed = 0;
    const uint32_t _duration = 120; // Movimento rápido

public:
    void attachModel(EyeModel* m) { _model = m; }
    
    // Evita o 'new'. Configura os alvos antes de dar play()
    void setTarget(float tx, float ty) {
        _targetX = tx;
        _targetY = ty;
    }

    void start() override {
        if (!_model) return;
        _startX = _model->get().pupilX;
        _startY = _model->get().pupilY;
        _elapsed = 0;
    }

    void update(uint32_t deltaMs) override {
        if (!_model) return;
        _elapsed += deltaMs;
        
        float t = (float)_elapsed / _duration;
        if (t > 1.0f) t = 1.0f;

        float eased = t * t; // Curva suave simples

        float nx = _startX + (_targetX - _startX) * eased;
        float ny = _startY + (_targetY - _startY) * eased;

        _model->setPupil(nx, ny);
    }

    bool finished() override { return _elapsed >= _duration; }
    int priority() const override { return 1; }
};