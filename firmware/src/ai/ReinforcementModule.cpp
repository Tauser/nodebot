#include "ReinforcementModule.h"

float ReinforcementModule::calculateReward(EventType event) {
    // Atribui pesos de reforço baseados no tipo de interação
    switch (event) {
        case EventType::INTERACTION_POSITIVE:
            return 0.10f; // Recompensa forte (ex: carinho)
            
        case EventType::INTERACTION_NEGATIVE:
            return -0.20f; // Punição forte (ex: abanão)
            
        case EventType::IGNORED:
            return -0.05f; // Punição leve (solidão)
            
        case EventType::LOUD_NOISE:
            return -0.10f; // Stress ambiental
            
        default:
            return 0.0f;
    }
}