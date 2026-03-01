#pragma once
#include "model/EyeModel.h"
#include "render/FaceRenderer.h"
#include "animation/Animation.h"
#include "animation/BlinkAnimation.h"
#include <vector>

class FaceService {
public:
    void init();
    void update(uint32_t deltaMs);
    
    // API de Alto Nível para o Cérebro usar
    void showEmotion(Emotion emotion);
    void triggerBlink();
    
private:
    EyeModel _model;
    FaceRenderer _renderer;
    
    // Lista de animações a correr neste momento (ex: piscar + olhar para o lado)
    std::vector<Animation*> _activeAnimations;
    
    // Instâncias de animações reutilizáveis (para não fazer 'new' a cada piscar)
    BlinkAnimation _blinkAnim;
    
    // Controlo do Piscar Automático
    uint32_t _timeUntilNextBlink = 0;
    void handleAutoBlink(uint32_t deltaMs);
    
    // Define a posição base dos olhos para cada emoção
    void applyEmotionBaseState(Emotion emotion);
};