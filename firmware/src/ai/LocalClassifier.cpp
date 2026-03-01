#include <Arduino.h>
#include "LocalClassifier.h"

bool LocalClassifier::classifyAudio(float volumeLevel, EventType& outEvent) {
    // Se o som passar de um limiar absurdo, classifica como barulho assustador
    if (volumeLevel > 0.85f) {
        outEvent = EventType::LOUD_NOISE;
        return true;
    }
    
    // Som vocal normal pode ser considerado interação positiva
    if (volumeLevel > 0.3f && volumeLevel <= 0.85f) {
        outEvent = EventType::INTERACTION_POSITIVE;
        return true;
    }
    
    return false; // Ruído de fundo ignorado
}

bool LocalClassifier::classifyVision(uint8_t brightnessDelta, EventType& outEvent) {
    // Se a câmara detetar uma mudança drástica e rápida de luz (alguém passou a mão perto)
    if (brightnessDelta > 80) {
        outEvent = EventType::INTERACTION_POSITIVE; // Considera uma tentativa de brincadeira
        return true;
    }
    
    return false;
}