#pragma once
#include <stdint.h>
#include "services/face/FaceService.h" // Para usar o Enum Emotion

enum class EventType {
    INTERACTION_POSITIVE, // Ex: Carinho longo
    INTERACTION_NEGATIVE, // Ex: Abanão brusco, bater
    IGNORED,              // Ex: Passou tempo sem estímulo
    LOUD_NOISE            // Susto sonoro
};

struct MemoryEntry {
    uint32_t timestamp;
    EventType event;
    Emotion emotionAtMoment;
    uint8_t intensity; // 0 a 100
};

class MemoryManager {
public:
    void init();
    
    // Regista um novo acontecimento na memória de curto prazo (Buffer Circular)
    void recordEvent(EventType event, Emotion currentEmotion, uint8_t intensity);
    
    // Analisa o histórico recente para tirar conclusões
    uint8_t getRecentEventCount(EventType type, uint32_t timeWindowMs) const;

private:
    static const int MAX_SHORT_TERM_MEMORIES = 50; // Limite fixo para não estourar a RAM
    MemoryEntry _shortTermMemory[MAX_SHORT_TERM_MEMORIES];
    int _headIndex; // Aponta para o espaço da memória mais antiga a ser sobrescrita
};