#pragma once

#include <stdint.h>
#include "../ai/EmotionModel.h" // Importa do local correto

struct InternalState {
    float energy;       // 0.0 (Exausto) a 1.0 (Cheio)
    float curiosity;    // 0.0 (Entediado) a 1.0 (Muito Curioso)
    float socialMood;   // -1.0 (Anti-social) a 1.0 (Sociável)
    Emotion currentEmotion;
};

class PersonalityService {
public:
    PersonalityService();

    void update(uint32_t deltaMs);

    // Getters
    const InternalState& getState() const;

    // Modificadores de estado (Inputs de sensores)
    void adjustEnergy(float delta);
    void adjustCuriosity(float delta);
    void adjustSocialMood(float delta);

private:
    InternalState _state;
    void determineEmotion();
};