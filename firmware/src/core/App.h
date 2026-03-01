#pragma once

// --- Sistema Nervoso ---
#include "core/EventBus.h"

// --- O Cérebro ---
#include "behavior/CognitiveLoop.h"

// --- Músculos e Sentidos ---
#include "services/face/FaceService.h"
// #include "services/MotionService.h"
// #include "services/TouchService.h"
// #include "services/AudioService.h"
// #include "services/VisionService.h"

// --- Sobrevivência e Feedback ---
// #include "services/PowerService.h"
// #include "services/StorageService.h"
#include "services/LightsService.h" // Usamos LedService para os teus LEDs

class App {
public:
    // Ponto de entrada chamado no main.cpp
    void init();

private:
    // --- Instâncias dos Órgãos (Todos ativos agora!) ---
    FaceService    _face;
    MotionService  _motion;
    // TouchService   _touch;
    // AudioService   _audio;
    // VisionService  _vision;
    // PowerService   _power;
    // StorageService _storage;
    LightsService     _leds;    // O serviço para os teus LEDs do pino 2
    
    // O Cérebro
    CognitiveLoop  _brain;

    // --- Gestão de Multicore (FreeRTOS) ---
    // Wrappers estáticos necessários para o SO
    static void faceTaskWrapper(void* param);
    static void brainTaskWrapper(void* param);
    
    // Loops internos de execução
    void runFaceLoop();
    void runBrainLoop();
};