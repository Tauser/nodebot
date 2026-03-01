#include "PersonalityService.h"
#include <Arduino.h>

void PersonalityService::init(AdaptiveModel* adaptiveModel) {
    _adaptiveModel = adaptiveModel;
    _state.energy = 1.0f;       
    _state.curiosity = 0.5f;    
    _state.stimulation = 0.0f;  
    _state.currentEmotion = Emotion::NEUTRAL;
}

void PersonalityService::update(uint32_t deltaMs) {
    float decayRate = deltaMs / 1000.0f;
    
    // LÊ A PERSONALIDADE APRENDIDA (Os Vieses)
    const PersonalityBiases& biases = _adaptiveModel->getBiases();
    
    // 1. Decaimento de Estímulo alterado pela Sociabilidade
    // Se o robô for muito sociável (bias > 0), o estímulo cai mais devagar. 
    // Se for anti-social (bias < 0), ele esquece a interação mais rápido.
    float stimDecay = 0.05f - (biases.sociabilityBias * 0.02f);
    if (stimDecay < 0.01f) stimDecay = 0.01f; // Limite mínimo
    
    _state.stimulation -= stimDecay * decayRate;

    // 2. Gasto de energia alterado pela Reatividade
    // Um robô reativo/assustadiço (bias > 0) queima energia mais rápido sob stress (estímulo alto)
    float energyDrain = 0.005f;
    if (_state.stimulation > 0.6f && biases.reactivityBias > 0.1f) {
        energyDrain += 0.01f * biases.reactivityBias; 
    }
    _state.energy -= energyDrain * decayRate; 

    // 3. Tédio vs Curiosidade
    if (_state.stimulation < 0.1f) {
        _state.curiosity -= 0.01f * decayRate;
    } else {
        // Se a Reatividade for alta, ele fica curioso MUITO mais depressa com qualquer ruído
        _state.curiosity += (0.02f + biases.reactivityBias * 0.01f) * decayRate;
    }

    // (O resto mantém-se igual: Clamps de segurança entre 0 e 1 e evaluateEmotion)
    if (_state.energy < 0.0f) _state.energy = 0.0f;
    if (_state.energy > 1.0f) _state.energy = 1.0f;
    if (_state.stimulation < 0.0f) _state.stimulation = 0.0f;
    if (_state.stimulation > 1.0f) _state.stimulation = 1.0f;
    if (_state.curiosity < 0.0f) _state.curiosity = 0.0f;
    if (_state.curiosity > 1.0f) _state.curiosity = 1.0f;

    evaluateEmotion();
}

void PersonalityService::addStimulus(float intensity) {
    _state.stimulation += intensity;
    if (_state.stimulation > 1.0f) _state.stimulation = 1.0f;
}

void PersonalityService::expendEnergy(float amount) {
    _state.energy -= amount;
}

void PersonalityService::rest(float amount) {
    _state.energy += amount;
}

void PersonalityService::evaluateEmotion() {
    // Busca os vieses da personalidade adaptativa
    const PersonalityBiases& biases = _adaptiveModel->getBiases();

    // DELEGA a decisão para o motor de Inteligência Artificial!
    _state.currentEmotion = _emotionModel.predict(
        _state.energy, 
        _state.stimulation, 
        _state.curiosity, 
        biases.sociabilityBias
    );
}

const InternalState& PersonalityService::getState() const {
    return _state;
}