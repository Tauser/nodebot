#pragma once

#include <stdint.h>

class ReflexEngine {
public:
    // Retorna true se um reflexo foi disparado (bloqueando o resto do cérebro)
    bool checkReflexes(float audioVolume, bool isTouched);

    // Retorna a emoção forçada pelo reflexo (ex: SCARED no susto)
    // Emotion getReflexEmotion() const; 
};