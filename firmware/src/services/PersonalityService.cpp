#include "PersonalityService.h"
#include <algorithm> // para std::clamp se disponível, ou usar macros

// Helper para limitar valores
float clamp(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

PersonalityService::PersonalityService() {
    // Estado inicial
    _state.energy = 1.0f;
    _state.curiosity = 0.5f;
    _state.socialMood = 0.0f;
    _state.currentEmotion = Emotion::NEUTRAL;
}

void PersonalityService::update(uint32_t deltaMs) {
    // Decaimento natural ao longo do tempo
    float decayFactor = deltaMs / 1000.0f; // Segundos

    // A energia cai lentamente com o tempo
    _state.energy -= 0.01f * decayFactor; 
    
    // A curiosidade cai se nada acontecer (tédio)
    _state.curiosity -= 0.05f * decayFactor;

    // Normalização dos valores
    _state.energy = clamp(_state.energy, 0.0f, 1.0f);
    _state.curiosity = clamp(_state.curiosity, 0.0f, 1.0f);
    _state.socialMood = clamp(_state.socialMood, -1.0f, 1.0f);

    determineEmotion();
}

void PersonalityService::adjustEnergy(float delta) {
    _state.energy = clamp(_state.energy + delta, 0.0f, 1.0f);
    determineEmotion();
}

void PersonalityService::adjustCuriosity(float delta) {
    _state.curiosity = clamp(_state.curiosity + delta, 0.0f, 1.0f);
    determineEmotion();
}

void PersonalityService::adjustSocialMood(float delta) {
    _state.socialMood = clamp(_state.socialMood + delta, -1.0f, 1.0f);
    determineEmotion();
}

const InternalState& PersonalityService::getState() const {
    return _state;
}

void PersonalityService::determineEmotion() {
    // Lógica Fuzzy simples para determinar emoção baseada em variáveis
    if (_state.energy < 0.2f) {
        _state.currentEmotion = Emotion::SLEEPY;
    } else if (_state.curiosity > 0.7f && _state.socialMood > 0.0f) {
        _state.currentEmotion = Emotion::EXCITED;
    } else if (_state.socialMood < -0.5f) {
        _state.currentEmotion = Emotion::ANGRY;
    } else {
        _state.currentEmotion = Emotion::NEUTRAL;
    }
}