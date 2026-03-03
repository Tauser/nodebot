#pragma once

enum class Expression { 
    NEUTRAL, HAPPY, ANGRY, SAD, SURPRISED, 
    FOCUSED, SKEPTIC, UNIMPRESSED, WORRIED, 
    FURIOUS, SQUINT, SUSPICIOUS 
};

struct EyeModel {
    Expression currentExpression = Expression::NEUTRAL;
    
    // Configurações de layout (Buffer 240x240)
    int baseWidth = 80;
    int baseHeight = 80;
    int defaultEyeY = 160; 
    int leftEyeX = 35;     
    int rightEyeX = 125;   

    // Estados dinâmicos para Delta Time
    float blinkFactor = 0.0f; 
    float leftScaleY = 1.0f;
    float rightScaleY = 1.0f;
    float currentSaccadeX = 0;
    float currentSaccadeY = 0;
};