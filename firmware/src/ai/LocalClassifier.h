#pragma once
#include <stdint.h>
#include "MemoryManager.h" // Para o EventType

class LocalClassifier {
public:
    // Tenta classificar o nível de áudio num evento reconhecível
    bool classifyAudio(float volumeLevel, EventType& outEvent);
    
    // Tenta classificar o padrão de luz captado pela câmara
    bool classifyVision(uint8_t brightnessDelta, EventType& outEvent);
};