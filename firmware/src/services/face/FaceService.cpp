#include "FaceService.h"
#include <Arduino.h>

void FaceService::init() {
    _renderer.init();
    
    // Liga a animação ao modelo
    _blinkAnim.attachModel(&_model);
    
    // Estado inicial
    _model.setPupil(0, 0);
    _model.setLid(1.0);
    _timeUntilNextBlink = 3000; // Começa a piscar daqui a 3s
}

void FaceService::update(uint32_t deltaMs) {
    // 1. Processa Animações Ativas
    for (size_t i = 0; i < _activeAnimations.size(); ) {
        Animation* anim = _activeAnimations[i];
        anim->update(deltaMs);
        
        if (anim->finished()) {
            // Remove animação da lista quando termina
            _activeAnimations.erase(_activeAnimations.begin() + i);
        } else {
            i++;
        }
    }
    
    // 2. Gere o Piscar Automático (Autonomic System)
    handleAutoBlink(deltaMs);
    
    // 3. Renderiza o estado final no ecrã
    _renderer.render(_model);
}

void FaceService::triggerBlink() {
    // Se já estiver a piscar, ignora para não encravar
    for(auto* a : _activeAnimations) {
        if (a == &_blinkAnim) return;
    }
    
    _blinkAnim.start();
    _activeAnimations.push_back(&_blinkAnim);
}

void FaceService::handleAutoBlink(uint32_t deltaMs) {
    if (_timeUntilNextBlink <= deltaMs) {
        triggerBlink();
        // Define o próximo piscar para um tempo aleatório entre 2s e 6s
        _timeUntilNextBlink = 2000 + (rand() % 4000);
    } else {
        _timeUntilNextBlink -= deltaMs;
    }
}

void FaceService::showEmotion(Emotion emotion) {
    applyEmotionBaseState(emotion);
}

void FaceService::applyEmotionBaseState(Emotion emotion) {
    switch(emotion) {
        case Emotion::NEUTRAL:
            _model.setPupilSize(1.0);
            _model.setLid(1.0);
            break;
        case Emotion::HAPPY:
            _model.setPupilSize(1.2); // Pupila grande = Fofura
            _model.setLid(1.0);
            break;
        case Emotion::SLEEPING:
            _model.setLid(0.0); // Olhos fechados
            break;
        case Emotion::SURPRISED:
            _model.setPupilSize(0.6); // Pupila pequena = Choque
            _model.setLid(1.0);
            break;
        default:
            _model.setPupilSize(1.0);
            _model.setLid(1.0);
            break;
    }
}