#include "StateMachine.h"

StateMachine::StateMachine() {
    _currentState = BotState::IDLE;
}

void StateMachine::update(bool faceDetected, float energyLevel, uint32_t timeSinceLastInteraction) {
    // Transições de Estado (Lógica de Alto Nível)
    
    switch (_currentState) {
        case BotState::IDLE:
            if (faceDetected) _currentState = BotState::OBSERVING;
            if (energyLevel < 0.1f) _currentState = BotState::SLEEPING;
            break;

        case BotState::OBSERVING:
            if (!faceDetected) _currentState = BotState::IDLE;
            // Se observar por 2 segundos, engaja interação
            // (Lógica simplificada para exemplo)
            if (faceDetected && timeSinceLastInteraction < 1000) _currentState = BotState::INTERACTING;
            break;

        case BotState::INTERACTING:
            if (!faceDetected && timeSinceLastInteraction > 5000) _currentState = BotState::IDLE;
            if (energyLevel < 0.05f) _currentState = BotState::SLEEPING;
            break;

        case BotState::SLEEPING:
            // Só acorda se a energia subir (carregando) ou evento extremo
            if (energyLevel > 0.2f) _currentState = BotState::IDLE;
            break;
    }
}