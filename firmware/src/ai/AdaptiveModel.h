#pragma once
#include "ai/MemoryManager.h"
#include "ai/ReinforcementModule.h" // <-- NOVO

struct PersonalityBiases {
    float sociabilityBias = 0.0f;  
    float explorationBias = 0.0f;  
    float reactivityBias = 0.0f;   
};

class AdaptiveModel {
public:
    void init(MemoryManager* memory);
    void adapt(uint32_t deltaMs);
    const PersonalityBiases& getBiases() const;

private:
    MemoryManager* _memory;
    ReinforcementModule _reinforcement; // <-- NOVO: O avaliador de peso
    PersonalityBiases _biases;
    uint32_t _adaptationTimer;
    
    void applyReinforcement();
};