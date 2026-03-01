#pragma once
#include <stdint.h>
#include "BehaviorCoordinator.h"
#include "ReflexEngine.h"
#include "StateMachine.h"
#include "services/PersonalityService.h"
#include "services/face/FaceService.h"
#include "services/MotionService.h"
#include "core/EventBus.h"

// --- FASE 5: Importações da Inteligência Adaptativa ---
#include "ai/MemoryManager.h"
#include "ai/AdaptiveModel.h"

class CognitiveLoop {
public:
    void init(FaceService* face, MotionService* motion);
    void tick();

private:
    // Fase 4: Motores Comportamentais
    PersonalityService _personality;
    BehaviorCoordinator _coordinator;
    ReflexEngine _reflexes;
    StateMachine _stateMachine; 

    // Fase 5: Módulos de IA / Aprendizado
    MemoryManager _memoryManager;  // <-- NOVO: O Hipocampo
    AdaptiveModel _adaptiveModel;  // <-- NOVO: A Neuroplasticidade

    FaceService* _face;         
    MotionService* _motion;     
    
    uint32_t _lastTickMs;       
    
    void evaluateStimuli();
};