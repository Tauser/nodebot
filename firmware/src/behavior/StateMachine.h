#pragma once

#include <stdint.h>

enum class BotState {
    IDLE,       // Nada a acontecer, economiza energia
    OBSERVING,  // Detectou algo, está a analisar
    INTERACTING,// Em interação ativa
    SLEEPING    // Bateria fraca ou inatividade longa
};

class StateMachine {
public:
    StateMachine();

    void update(bool faceDetected, float energyLevel, uint32_t timeSinceLastInteraction);
    
    BotState getCurrentState() const { return _currentState; }

private:
    BotState _currentState;
};