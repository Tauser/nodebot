#pragma once
#include <LovyanGFX.hpp>
#include "../model/EyeModel.h"
#include "../animation/EmotionTransition.h"

// Estrutura para o Dirty Rectangle
struct BoundingBox {
    int x, y, w, h;
};

class FaceRenderer {
public:
    void init(lgfx::LGFX_Sprite* spriteBuffer);
    
    // Agora o render retorna a área exata que precisa ser atualizada no display
    BoundingBox render(const EyeModel& model, float dt, const EmotionTransition& et);

private:
    lgfx::LGFX_Sprite* canvas;
    lgfx::LGFX_Sprite baseSprite, happyMask, angryMask, sadMask, focusedMask;
    
    // Armazena a área do frame anterior para podermos apagar o rastro
    int lastMinX = 0, lastMinY = 0, lastMaxX = 240, lastMaxY = 240; 
};