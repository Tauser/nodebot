#pragma once
#include "model/EyeModel.h"
#include "animation/AnimationEngine.h"
#include "render/FaceRenderer.h"
#include "../../drivers/DisplayDriver.h" // Inclui o seu driver limpo

class FaceService {
private:
    lgfx::LGFX_Sprite canvas; // O nosso Sprite (Tela virtual)
    lgfx::LGFX_Device* _tft;
    
    EyeModel model;
    AnimationEngine animator;
    FaceRenderer renderer;

public:
    // O construtor não precisa mais inicializar o display direto
    FaceService() {} 

    // Passamos o DisplayDriver por referência na inicialização
    void begin(DisplayDriver& driver);
    void update();
    void setExpression(Expression expr);
};