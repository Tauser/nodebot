#include "CognitiveLoop.h"
#include <Arduino.h> // Para logs ou funções específicas do ESP32

CognitiveLoop::CognitiveLoop(PersonalityService& personality, BehaviorCoordinator& coordinator)
    : _personality(personality), _coordinator(coordinator) {
}

void CognitiveLoop::update(uint32_t deltaMs) {
    // 1. Avaliar Estímulos e Reflexos (Rápido)
    evaluateStimuli();
    
    // Se um reflexo disparou (ex: susto), interrompe o pensamento racional
    // if (_reflexEngine.checkReflexes(audioLevel, touch)) return;

    // 2. Atualizar Máquina de Estados (Contexto)
    // _stateMachine.update(faceDetected, _personality.getState().energy, 0);

    // 3. Atualizar Estado Interno (Emoções e Variáveis)
    updateInternalState(deltaMs);

    // 4. Escolher Comportamento (Decisão Racional)
    chooseBehavior();

    // 5. Executar Comportamento (Ação)
    executeBehavior();
}

void CognitiveLoop::evaluateStimuli() {
    // Aqui você coletaria dados do EventBus ou Sensores
    // Exemplo:
    // if (VisionService::hasFace()) {
    //     _coordinator.setFaceDetected(true, x, y);
    //     _personality.adjustCuriosity(0.1f); // Ver rosto aumenta curiosidade
    // }
}

void CognitiveLoop::updateInternalState(uint32_t deltaMs) {
    _personality.update(deltaMs);
}

void CognitiveLoop::chooseBehavior() {
    _coordinator.arbitrate(_personality.getState());
}

void CognitiveLoop::executeBehavior() {
    FaceCommand cmd = _coordinator.getLatestFaceCommand();
    
    if (cmd.isValid) {
        // Enviar para o FaceService
        // FaceService::getInstance()->setExpression(cmd.emotion);
        // FaceService::getInstance()->lookAt(cmd.attentionFocusX, cmd.attentionFocusY);
        // Serial.printf("Executando: Emoção %d, Olhar X:%.2f\n", (int)cmd.emotion, cmd.attentionFocusX);
    }
}