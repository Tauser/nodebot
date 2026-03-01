#pragma once
#include "services/face/FaceService.h" // Para o enum Emotion

class EmotionModel {
public:
    // Recebe a química atual e os vieses da personalidade para inferir a emoção
    Emotion predict(float energy, float stimulation, float curiosity, float sociabilityBias);
};

