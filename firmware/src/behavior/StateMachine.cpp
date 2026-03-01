#include "StateMachine.h"
#include <Arduino.h>

void StateMachine::init(FaceService* face, MotionService* motion) {
    _face = face;
    _motion = motion;
    _currentState = BotState::BOOTING;
    _timeInStateMs = 0;
    
    // Arranca o sistema em IDLE
    changeState(BotState::IDLE);
}

void StateMachine::update(uint32_t deltaMs) {
    _timeInStateMs += deltaMs;

    // A StateMachine executa a "manutenção" do estado.
    // Decisões de MUDAR de estado não são feitas aqui, mas no Coordinator.
    switch (_currentState) {
        case BotState::IDLE:
            // Exemplo: Vida de fundo. A cada 10 segundos, olha em redor.
            if (_timeInStateMs > 10000) {
                _timeInStateMs = 0; // Reseta o timer local
                // (Aqui poderíamos chamar uma coreografia leve no MotionService)
            }
            break;
            
        case BotState::SLEEPING:
            // Opcional: A cada X segundos, altera levemente a respiração
            break;
            
        case BotState::OBSERVING:
            // Fica focado num ponto fixo avaliando
            break;

        default:
            break;
    }
}

void StateMachine::changeState(BotState newState) {
    if (_currentState == newState) return; // Evita loop infinito

    // 1. Desmonta o estado antigo
    onExitState(_currentState);
    
    // 2. Altera o ponteiro
    _currentState = newState;
    _timeInStateMs = 0;
    
    // 3. Monta o estado novo
    onEnterState(_currentState);
}

void StateMachine::onEnterState(BotState state) {
    // A primeira coisa que o robô faz assim que entra num estado novo
    switch (state) {
        case BotState::IDLE:
            _face->showEmotion(Emotion::NEUTRAL);
            _motion->lookCenter();
            break;
            
        case BotState::OBSERVING:
            _face->showEmotion(Emotion::SURPRISED); // Olhos abertos para captar dados
            break;
            
        case BotState::INTERACTING:
            _face->showEmotion(Emotion::HAPPY);
            break;
            
        case BotState::SLEEPING:
            _face->showEmotion(Emotion::SLEEPING);
            _motion->lookDown(); // A cabeça "cai" ao dormir
            break;
            
        default:
            break;
    }
}

void StateMachine::onExitState(BotState state) {
    // Limpezas de saída (Ex: parar um som de ressonar ao sair do SLEEPING)
    switch (state) {
        case BotState::SLEEPING:
            _face->triggerBlink(); // Pisca os olhos a acordar
            break;
        default:
            break;
    }
}

BotState StateMachine::getCurrentState() const {
    return _currentState;
}

uint32_t StateMachine::getTimeInState() const {
    return _timeInStateMs;
}