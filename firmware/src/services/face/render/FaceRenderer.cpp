#include "FaceRenderer.h"

void FaceRenderer::init(lgfx::LGFX_Sprite* spriteBuffer) {
    canvas = spriteBuffer;
}

void FaceRenderer::render(const EyeModel& model) {
    // Serial.println(model.blinkFactor); // REMOVIDO: Evita travar o loop se o buffer serial encher
    
    // canvas->fillScreen(TFT_BLACK); // REMOVIDO: Usaremos Dirty Rectangles para limpar apenas o necessário

    // 1. Alturas independentes para humanização (Assimetria)
    int hL = model.baseHeight * model.blinkFactor * model.leftScaleY;
    int hR = model.baseHeight * model.blinkFactor * model.rightScaleY;
    
    // 2. Parâmetros de geometria
    int w = model.baseWidth;
    int r = model.baseRadius;
    if (model.blinkFactor < 0.3) r = 4; // Borda dura ao fechar

    // 3. Posições Y independentes (Mantém o Saccade)
    int yL = model.defaultEyeY + (model.baseHeight - hL) + model.currentSaccadeY;
    int yR = model.defaultEyeY + (model.baseHeight - hR) + model.currentSaccadeY;

    // 4. Posições X com Saccade
    int lx = model.leftEyeX + model.currentSaccadeX;
    int rx = model.rightEyeX + model.currentSaccadeX;

    // --- OTIMIZAÇÃO: DIRTY RECTANGLES ---
    // Limpa apenas a área onde os olhos estavam no quadro anterior
    static int last_lx, last_yL, last_w, last_hL;
    static int last_rx, last_yR, last_hR;
    static bool initialized = false;
    const int PAD = 10; // Margem de segurança para cobrir expressões maiores (ex: Skeptic)

    if (initialized) {
        // Limpa olho esquerdo anterior
        canvas->fillRect(last_lx - PAD, last_yL - PAD, last_w + 2*PAD, last_hL + 2*PAD, TFT_BLACK);
        // Limpa olho direito anterior
        canvas->fillRect(last_rx - PAD, last_yR - PAD, last_w + 2*PAD, last_hR + 2*PAD, TFT_BLACK);
        // Limpa a área do contador de FPS
        canvas->fillRect(5, 5, 120, 20, TFT_BLACK);
    } else {
        canvas->fillScreen(TFT_BLACK); // Limpa tudo apenas no primeiro quadro
        initialized = true;
    }
    // Salva coordenadas atuais para serem limpas no próximo quadro
    last_lx = lx; last_yL = yL; last_w = w; last_hL = hL;
    last_rx = rx; last_yR = yR; last_hR = hR;

    // 5. Lógica de Desenho Principal
    if (model.blinkFactor < 0.2) {
        canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
        canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    } else {
        switch (model.currentExpression) {
            case Expression::NEUTRAL:    drawNeutralGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::HAPPY:      drawHappyGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::ANGRY:      drawAngryGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::SAD:        drawSadGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::SURPRISED:  drawSurprisedGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::FOCUSED:    drawFocusedGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::SKEPTIC:    drawSkepticGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::UNIMPRESSED:drawUnimpressedGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::WORRIED:    drawWorriedGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::FURIOUS:    drawFuriousGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::SQUINT:     drawSquintGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
            case Expression::SUSPICIOUS: drawSuspiciousGeometry(lx, rx, yL, yR, w, hL, hR, r); break;
        }
    }

    // --- MEDIDOR DE FPS ---
    static uint32_t lastFpsTime = 0;
    static int frameCount = 0;
    static int fps = 0;

    frameCount++;
    if (millis() - lastFpsTime >= 1000) {
        fps = frameCount;
        frameCount = 0;
        lastFpsTime = millis();
    }

    canvas->setCursor(5, 5);      // Canto superior esquerdo
    canvas->setTextColor(0x07E0); // Cor Verde (TFT_GREEN)
    canvas->setTextSize(2);       // Tamanho legível
    canvas->print("FPS: ");
    canvas->print(fps);
}

// --- IMPLEMENTAÇÃO DAS GEOMETRIAS ---

void FaceRenderer::drawNeutralGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
}

void FaceRenderer::drawHappyGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillCircle(lx + w/2, yL + hL * 1.2, w * 0.8, TFT_BLACK); 
    canvas->fillCircle(rx + w/2, yR + hR * 1.2, w * 0.8, TFT_BLACK); 
}

void FaceRenderer::drawAngryGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillTriangle(lx + w/2, yL - 4, lx + w + 4, yL - 4, lx + w + 4, yL + hL/2, TFT_BLACK);
    canvas->fillTriangle(rx + w/2, yR - 4, rx - 4, yR - 4, rx - 4, yR + hR/2, TFT_BLACK);
}

void FaceRenderer::drawSadGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillTriangle(lx + w/2, yL - 4, lx - 4, yL - 4, lx - 4, yL + hL/2, TFT_BLACK);
    canvas->fillTriangle(rx + w/2, yR - 4, rx + w + 4, yR - 4, rx + w + 4, yR + hR/2, TFT_BLACK);
}

void FaceRenderer::drawSurprisedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
}

void FaceRenderer::drawFocusedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL - 4, w + 8, hL/3, TFT_BLACK); 
    canvas->fillRect(rx - 4, yR - 4, w + 8, hR/3, TFT_BLACK);
    canvas->fillRect(lx - 4, yL + hL - hL/3 + 4, w + 8, hL/3, TFT_BLACK); 
    canvas->fillRect(rx - 4, yR + hR - hR/3 + 4, w + 8, hR/3, TFT_BLACK);
}

void FaceRenderer::drawSkepticGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL - 4, w + 8, hL/3, TFT_BLACK); 
    canvas->fillRect(lx - 4, yL + hL - hL/3 + 4, w + 8, hL/3, TFT_BLACK); 
    canvas->fillRoundRect(rx, yR - 5, w, hR + 10, r, TFT_WHITE);
    canvas->fillTriangle(rx - 4, yR - 15, rx + w + 4, yR + (hR / 2), rx + w + 4, yR - 20, TFT_BLACK);
}

void FaceRenderer::drawUnimpressedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL - 4, w + 8, hL * 0.65, TFT_BLACK);
    canvas->fillRect(rx - 4, yR - 4, w + 8, hR * 0.65, TFT_BLACK);
}

void FaceRenderer::drawWorriedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL + hL - (hL/4), w + 8, (hL/4) + 4, TFT_BLACK);
    canvas->fillRect(rx - 4, yR + hR - (hR/4), w + 8, (hR/4) + 4, TFT_BLACK);
    canvas->fillTriangle(lx + w/2, yL - 4, lx - 4, yL - 4, lx - 4, yL + hL/3, TFT_BLACK); 
    canvas->fillTriangle(rx + w/2, yR - 4, rx + w + 4, yR - 4, rx + w + 4, yR + hR/3, TFT_BLACK); 
}

void FaceRenderer::drawFuriousGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL + hL/4, w, hL - hL/4, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR + hR/4, w, hR - hR/4, r, TFT_WHITE);
    canvas->fillTriangle(lx + w + 4, yL - 4, lx - w/2, yL - 4, lx + w + 4, yL + hL, TFT_BLACK);
    canvas->fillTriangle(rx - 4, yR - 4, rx + w + w/2, yR - 4, rx - 4, yR + hR, TFT_BLACK);
}

void FaceRenderer::drawSquintGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL - 4, w + 8, hL * 0.4, TFT_BLACK); 
    canvas->fillRect(rx - 4, yR - 4, w + 8, hR * 0.4, TFT_BLACK); 
    canvas->fillRect(lx - 4, yL + hL - (hL * 0.4) + 4, w + 8, hL * 0.4, TFT_BLACK); 
    canvas->fillRect(rx - 4, yR + hR - (hR * 0.4) + 4, w + 8, hR * 0.4, TFT_BLACK); 
}

void FaceRenderer::drawSuspiciousGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r) {
    canvas->fillRoundRect(lx, yL, w, hL, r, TFT_WHITE);
    canvas->fillRect(lx - 4, yL - 4, w + 8, hL * 0.45, TFT_BLACK); 
    canvas->fillRect(lx - 4, yL + hL - (hL * 0.45) + 4, w + 8, hL * 0.45, TFT_BLACK); 
    canvas->fillRoundRect(rx, yR, w, hR, r, TFT_WHITE);
    canvas->fillRect(rx - 4, yR - 4, w + 8, hR * 0.3, TFT_BLACK); 
}