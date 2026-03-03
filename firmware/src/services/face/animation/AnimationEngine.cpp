#include "AnimationEngine.h"

AnimationEngine::AnimationEngine() {
    // Registra as animações no vetor para processamento em lote
    animations.push_back(&blink);
    animations.push_back(&saccade);
    animations.push_back(&transition);
    animations.push_back(&scan);
    animations.push_back(&impact);
    animations.push_back(&idle);
}

void AnimationEngine::update(EyeModel& model, float dt) {
    // Executa o update de cada módulo registrado
    for (auto anim : animations) {
        anim->update(model, dt);
    }
}