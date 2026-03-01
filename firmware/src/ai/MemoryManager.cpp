#include <Arduino.h>
#include "MemoryManager.h"

void MemoryManager::init() {
    _headIndex = 0;
    // Limpa o buffer de memória inicial preenchendo com zeros
    for (int i = 0; i < MAX_SHORT_TERM_MEMORIES; i++) {
        _shortTermMemory[i].timestamp = 0;
    }
}

void MemoryManager::recordEvent(EventType event, Emotion currentEmotion, uint8_t intensity) {
    // Insere no índice atual
    _shortTermMemory[_headIndex].timestamp = millis();
    _shortTermMemory[_headIndex].event = event;
    _shortTermMemory[_headIndex].emotionAtMoment = currentEmotion;
    _shortTermMemory[_headIndex].intensity = intensity;

    // Avança o ponteiro de forma circular (se chegar a 50, volta a 0 e apaga a memória mais velha)
    _headIndex = (_headIndex + 1) % MAX_SHORT_TERM_MEMORIES;
}

uint8_t MemoryManager::getRecentEventCount(EventType type, uint32_t timeWindowMs) const {
    uint8_t count = 0;
    uint32_t now = millis();

    for (int i = 0; i < MAX_SHORT_TERM_MEMORIES; i++) {
        const MemoryEntry& entry = _shortTermMemory[i];
        
        // Ignora memórias vazias ou que aconteceram antes da janela de tempo desejada
        if (entry.timestamp == 0) continue;
        if (now - entry.timestamp > timeWindowMs) continue;

        if (entry.event == type) {
            count++;
        }
    }
    return count;
}