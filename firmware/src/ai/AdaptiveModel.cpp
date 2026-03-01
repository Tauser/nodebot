#include "AdaptiveModel.h"

void AdaptiveModel::init(MemoryManager* memory) {
    _memory = memory;
    _adaptationTimer = 0;
    
    // Robô começa "tábula rasa" (neutro)
    _biases.sociabilityBias = 0.0f;
    _biases.explorationBias = 0.0f;
    _biases.reactivityBias = 0.0f;
}

void AdaptiveModel::adapt(uint32_t deltaMs) {
    _adaptationTimer += deltaMs;
    
    // A adaptação de personalidade é lenta. Só avaliamos a cada 10 segundos.
    if (_adaptationTimer < 10000) return;
    _adaptationTimer = 0;

    applyReinforcement();
}

void AdaptiveModel::applyReinforcement() {
    uint32_t analysisWindow = 300000; // 5 minutos

    // Usa o Professor (ReinforcementModule) para descobrir o "peso" matemático de cada evento
    float rewardPositiva = _reinforcement.calculateReward(EventType::INTERACTION_POSITIVE);
    float rewardNegativa = _reinforcement.calculateReward(EventType::INTERACTION_NEGATIVE);
    float rewardIgnorado = _reinforcement.calculateReward(EventType::IGNORED);

    uint8_t countPositive = _memory->getRecentEventCount(EventType::INTERACTION_POSITIVE, analysisWindow);
    uint8_t countNegative = _memory->getRecentEventCount(EventType::INTERACTION_NEGATIVE, analysisWindow);
    uint8_t countIgnored = _memory->getRecentEventCount(EventType::IGNORED, analysisWindow);

    // Aplica as recompensas (Pesos da IA) diretamente nos vieses da personalidade
    _biases.sociabilityBias += (countPositive * rewardPositiva) + (countIgnored * rewardIgnorado);
    
    // Experiências negativas aumentam a reatividade (medo/trauma). Se não houver, diminui lentamente.
    if (countNegative > 0) {
        _biases.reactivityBias += (countNegative * (rewardNegativa * -1.0f)); 
    } else {
        _biases.reactivityBias -= 0.01f;
    }

    // Clamps de segurança estrutural (-0.5 a +0.5)
    if (_biases.sociabilityBias > 0.5f) _biases.sociabilityBias = 0.5f;
    if (_biases.sociabilityBias < -0.5f) _biases.sociabilityBias = -0.5f;
    if (_biases.reactivityBias > 0.5f) _biases.reactivityBias = 0.5f;
    if (_biases.reactivityBias < -0.5f) _biases.reactivityBias = -0.5f;
}

const PersonalityBiases& AdaptiveModel::getBiases() const {
    return _biases;
}