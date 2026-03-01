#include "CognitiveLoop.h"
#include <Arduino.h>

void CognitiveLoop::init(FaceService* face, MotionService* motion) {
    _face = face;
    _motion = motion;

    // 1. Inicializa a Memória e Adaptação (Fase 5)
    _memoryManager.init();
    _adaptiveModel.init(&_memoryManager);

    // 2. Inicializa a Personalidade (injetando os vieses da Fase 5)
    _personality.init(&_adaptiveModel);

    // 3. Inicializa a Arquitetura Comportamental (Fase 4)
    _stateMachine.init(_face, _motion);
    _reflexes.init(_face, _motion);
    _coordinator.init(&_personality, _face, _motion, &_stateMachine);
    
    _lastTickMs = millis();
}

void CognitiveLoop::tick() {
    uint32_t now = millis();
    uint32_t deltaMs = now - _lastTickMs;
    
    // Limita o cérebro a rodar a 20Hz (50ms)
    if (deltaMs < 50) return; 
    _lastTickMs = now;

    // 1. Ler Entradas do EventBus
    evaluateStimuli();

    // 2. Atualiza Química Interna
    _personality.update(deltaMs);

    // 3. Evolução/Adaptação Lenta (FASE 5)
    _adaptiveModel.adapt(deltaMs);

    // 4. Manutenção de Estados
    _stateMachine.update(deltaMs);

    // 5. O Árbitro toma a decisão final
    _coordinator.arbitrate();
}

void CognitiveLoop::evaluateStimuli() {
    EventMessage msg;
    
    // Processa TODAS as mensagens que estão na fila neste tick
    while (Bus.consume(msg)) {
        switch (msg.type) {
            case SystemEvent::TOUCH_PETTING:
                _personality.addStimulus(0.6f); 
                _personality.rest(0.2f); // Carinho relaxa o robô
                break;
                
            case SystemEvent::LOUD_NOISE:
                _reflexes.onLoudNoise(); // Dispara o reflexo instantâneo!
                _personality.expendEnergy(0.1f); // Assustar gasta energia
                break;
                
            default:
                break;
        }
    }
}