#pragma once
#include "MemoryManager.h" // Para o EventType

class ReinforcementModule {
public:
    // Avalia o peso (recompensa/punição) de um evento específico
    float calculateReward(EventType event);
};