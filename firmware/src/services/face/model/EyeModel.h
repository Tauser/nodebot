#pragma once

enum class Expression { 
    NEUTRAL, HAPPY, ANGRY, SAD, SURPRISED, 
    FOCUSED, SKEPTIC, UNIMPRESSED, WORRIED, 
    FURIOUS, SQUINT, SUSPICIOUS 
};

enum class BlinkState { EYE_OPEN, EYE_CLOSING, EYE_CLOSED, EYE_OPENING };

struct EyeModel {
    Expression currentExpression = Expression::NEUTRAL;
    BlinkState blinkState = BlinkState::EYE_OPEN;

    // Geometria Base Escalonada (Para Tela 320x240)
    int baseWidth = 80;
    int baseHeight = 80;
    int baseRadius = 16;
    int defaultEyeY = 80;
    int leftEyeX = 55;
    int rightEyeX = 185;

    // Variáveis Dinâmicas de Animação
    float blinkFactor = 1.0; 
    float currentSaccadeX = 0;
    float currentSaccadeY = 0;
    
    // --- NOVIDADE: HUMANIZAÇÃO (ASSIMETRIA) ---
    // Começam em 1.0 para o olho aparecer normalmente
    float leftScaleY = 1.0;  
    float rightScaleY = 1.0;
    float targetLeftScaleY = 1.0;
    float targetRightScaleY = 1.0;

    // Controle da "Personalidade" do tempo
    unsigned long blinkInterval = 4000;
};