#pragma once
#include "services/PersonalityService.h"
#include "services/face/FaceService.h"
#include "services/MotionService.h"
#include "StateMachine.h" // <-- IMPORTAÇÃO QUE FALTAVA

class BehaviorCoordinator {
public:
    // Assinatura atualizada para receber a StateMachine
    void init(PersonalityService* personality, FaceService* face, MotionService* motion, StateMachine* stateMachine);
    
    void arbitrate();

private:
    PersonalityService* _personality;
    FaceService* _face;
    MotionService* _motion;
    StateMachine* _stateMachine; // <-- VARIÁVEL QUE FALTAVA
};