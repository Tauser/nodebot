#include "BehaviorCoordinator.h"

void BehaviorCoordinator::init(PersonalityService* personality, FaceService* face, MotionService* motion, StateMachine* stateMachine) {
    _personality = personality;
    _face = face;
    _motion = motion;
    _stateMachine = stateMachine; // Injetamos a state machine aqui
}

void BehaviorCoordinator::arbitrate() {
    const InternalState& state = _personality->getState();
    BotState currentState = _stateMachine->getCurrentState();

    // 1. Regra de Sobrevivência Vital (Bateria/Energia Interna)
    if (state.energy < 0.1f && currentState != BotState::SLEEPING) {
        _stateMachine->changeState(BotState::SLEEPING);
        return; // Prioridade máxima, sai da função
    }

    // 2. Acordar Naturalmente
    if (state.energy > 0.8f && currentState == BotState::SLEEPING) {
        _stateMachine->changeState(BotState::IDLE);
        return;
    }

    // 3. Reação ao Estímulo
    if (currentState == BotState::IDLE) {
        if (state.stimulation > 0.5f) {
            _stateMachine->changeState(BotState::OBSERVING);
        }
    }
    else if (currentState == BotState::OBSERVING) {
        if (state.stimulation < 0.1f && _stateMachine->getTimeInState() > 5000) {
            // Se ficou calmo por 5 segundos, volta a relaxar
            _stateMachine->changeState(BotState::IDLE);
        }
    }

    // 4. Aplica a emoção dominante calculada pela Personalidade
    // (Apenas se não estiver a dormir, pois a StateMachine já controla a cara no sono)
    if (currentState != BotState::SLEEPING) {
        _face->showEmotion(state.currentEmotion);
    }
}