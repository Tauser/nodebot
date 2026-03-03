#pragma once

#include <stdint.h>
#include "../services/PersonalityService.h"
#include "BehaviorCoordinator.h"
#include "ReflexEngine.h"
#include "StateMachine.h"

// Forward declarations dos serviços que serão controlados
// class FaceService; 
// class MotionService;

class CognitiveLoop {
public:
    CognitiveLoop(PersonalityService& personality, BehaviorCoordinator& coordinator);

    void update(uint32_t deltaMs);

private:
    PersonalityService& _personality;
    BehaviorCoordinator& _coordinator;
    
    // Componentes Comportamentais
    ReflexEngine _reflexEngine;
    StateMachine _stateMachine;

    void evaluateStimuli();
    void updateInternalState(uint32_t deltaMs);
    void chooseBehavior();
    void executeBehavior();
};