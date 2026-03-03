#pragma once

#include <stdint.h>
#include "../drivers/DisplayDriver.h" // <-- O nosso novo driver de hardware
#include "../services/face/FaceService.h"
#include "../services/PersonalityService.h"
#include "../services/AudioService.h"
#include "../behavior/CognitiveLoop.h"
#include "../behavior/BehaviorCoordinator.h"

class App {
public:
    App();
    void init(); 
    void loop();

private:
    void runFaceLoop();
    void runBrainLoop();
    void processSerialCommands();

    // Hardware Drivers
    DisplayDriver _displayDriver; 

    // Serviços
    FaceService _face;
    AudioService _audio;
    PersonalityService _personality;
    
    // Comportamento (Cérebro)
    BehaviorCoordinator _coordinator;
    CognitiveLoop _brain;
    
    uint32_t _lastBrainUpdate = 0;
    uint32_t _lastFaceUpdate = 0;
};

