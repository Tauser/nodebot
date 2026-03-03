#include "LocalClassifier.h"

bool LocalClassifier::classifyAudio(float volume, EventType& detectedType) {
    if (volume > 0.8f) {
        detectedType = EventType::LOUD_NOISE;
        return true;
    }
    // Lógica futura para detetar padrões de voz
    
    detectedType = EventType::NONE;
    return false;
}