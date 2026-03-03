#include "ReflexEngine.h"
#include <Arduino.h>

bool ReflexEngine::checkReflexes(float audioVolume, bool isTouched) {
    // Regra 1: Som muito alto causa susto imediato (Startle Response)
    if (audioVolume > 0.85f) {
        // TODO: Disparar animação de susto diretamente aqui ou via EventBus
        return true; 
    }

    // Regra 2: Toque súbito pode causar reação rápida
    // (Implementação futura dependendo da sensibilidade)
    
    return false;
}