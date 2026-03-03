#include "FaceRenderer.h"

void FaceRenderer::init(lgfx::LGFX_Sprite* spriteBuffer) {
    canvas = spriteBuffer;
    
    // OTIMIZAÇÃO: Reduzindo os sprites pre-renderizados para 8-bit
    baseSprite.createSprite(80, 80); 
    baseSprite.fillRoundRect(0, 0, 80, 80, 16, TFT_WHITE);
    
    happyMask.createSprite(100, 100); 
    happyMask.fillCircle(50, 115, 80, TFT_BLACK);
    
    angryMask.createSprite(80, 40); 
    angryMask.fillTriangle(0, 0, 80, 0, 80, 40, TFT_BLACK);
    
    sadMask.createSprite(80, 40); 
    sadMask.fillTriangle(0, 0, 80, 0, 0, 40, TFT_BLACK);
    
    focusedMask.createSprite(80, 40); 
    focusedMask.fillRect(0, 0, 80, 40, TFT_BLACK);
}

BoundingBox FaceRenderer::render(const EyeModel& model, float dt, const EmotionTransition& et) {
    int lx = model.leftEyeX + (int)model.currentSaccadeX;
    int rx = model.rightEyeX + (int)model.currentSaccadeX;
    int yBase = model.defaultEyeY + (int)model.currentSaccadeY;
    float sF = 1.0f + (et.surprisedW * 0.4f);

    // 1. Calcula a área ocupada neste frame (com margem de segurança)
    int currentMinX = max(0, lx - 20);
    int currentMaxX = min(240, rx + 100);
    int currentMinY = max(0, yBase - 100);
    int currentMaxY = min(240, yBase + (int)(80 * sF) + 10);

    // 2. A "Área Suja" real é a UNIÃO entre onde o olho estava e onde ele está agora
    int dirtyX = min(lastMinX, currentMinX);
    int dirtyY = min(lastMinY, currentMinY);
    int dirtyW = max(lastMaxX, currentMaxX) - dirtyX;
    int dirtyH = max(lastMaxY, currentMaxY) - dirtyY;

    // 3. Limpa APENAS o Dirty Rectangle (Adeus fillScreen pesado!)
    canvas->fillRect(dirtyX, dirtyY, dirtyW, dirtyH, TFT_BLACK);

    // Atualiza o lastFrame para a próxima iteração
    lastMinX = currentMinX; lastMaxX = currentMaxX;
    lastMinY = currentMinY; lastMaxY = currentMaxY;

    // --- DESENHO ---
    baseSprite.setPivot(40, 80);
    baseSprite.pushRotateZoom(canvas, (float)(lx+40), (float)yBase, 0.0f, sF, (float)(model.leftScaleY * model.blinkFactor * sF));
    baseSprite.pushRotateZoom(canvas, (float)(rx+40), (float)yBase, 0.0f, sF, (float)(model.rightScaleY * model.blinkFactor * sF));

    auto drawMask = [&](lgfx::LGFX_Sprite& m, int x, int y, float w, bool mirror = false) {
        if (w > 0.01f) {
            if (!mirror) m.pushSprite(canvas, x, y, TFT_BLACK);
            else { m.setPivot(40, 20); m.pushRotateZoom(canvas, (float)(x+40), (float)(y+20), 0.0f, -1.0f, 1.0f, TFT_BLACK); }
        }
    };

    drawMask(happyMask, lx-10, yBase+(int)(15-et.happyW*45), et.happyW);
    drawMask(happyMask, rx-10, yBase+(int)(15-et.happyW*45), et.happyW);

    if (et.angryW > 0.01f || et.furiousW > 0.01f) {
        int aY = yBase - 85 + (int)(max(et.angryW, et.furiousW)*35);
        drawMask(angryMask, lx, aY, 1.0f); drawMask(angryMask, rx, aY, 1.0f, true);
    }

    // Retorna as coordenadas exatas da área que mudou
    return {dirtyX, dirtyY, dirtyW, dirtyH};
}