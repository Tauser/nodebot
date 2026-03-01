#pragma once
#include <stdint.h>
#include "services/face/FaceService.h"
#include "services/MotionService.h"

// Os "Macros" Contextuais do Robô
enum class BotState {
    BOOTING,
    IDLE,        // Relaxado, poupando energia
    OBSERVING,   // Atento ao ambiente (ex: ouviu algo)
    INTERACTING, // Focado numa pessoa (Tato ou Visão)
    SLEEPING     // Em repouso absoluto
};

class StateMachine {
public:
    void init(FaceService* face, MotionService* motion);
    
    // Atualiza a vida de fundo do estado atual (ex: ressonar enquanto dorme)
    void update(uint32_t deltaMs);
    
    // O Árbitro (Coordinator) chama isto para forçar uma transição
    void changeState(BotState newState);
    
    BotState getCurrentState() const;
    uint32_t getTimeInState() const; // Útil para timeouts

private:
    BotState _currentState;
    FaceService* _face;
    MotionService* _motion;

    uint32_t _timeInStateMs;

    // Funções internas de transição rigorosa
    void onEnterState(BotState state);
    void onExitState(BotState state);
};