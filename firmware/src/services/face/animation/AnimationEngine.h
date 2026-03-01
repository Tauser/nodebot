#pragma once
#include "Animation.h"

class AnimationEngine {
private:
    Animation* _current = nullptr;
    Animation* _overlay = nullptr;

public:
    void update(uint32_t deltaMs) {
        // Overlay (Ex: Piscada) tem prioridade absoluta de update e ignora a animação base
        if (_overlay) {
            _overlay->update(deltaMs);
            if (_overlay->finished()) _overlay = nullptr;
        }

        // Animação base (Ex: Saccade ou Transição de Emoção)
        if (_current) {
            _current->update(deltaMs);
            if (_current->finished()) _current = nullptr;
        }
    }

    void play(Animation* anim) {
        if (!_current || anim->priority() >= _current->priority()) {
            _current = anim;
            _current->start();
        }
    }

    void playOverlay(Animation* anim) {
        _overlay = anim;
        _overlay->start();
    }
};