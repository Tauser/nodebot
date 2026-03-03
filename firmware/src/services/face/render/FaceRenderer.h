#pragma once
#include <LovyanGFX.hpp>
#include "../model/EyeModel.h"

class FaceRenderer {
private:
    lgfx::LGFX_Sprite* canvas;

    // Protótipos das 12 funções geométricas de máscara
    void drawNeutralGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawHappyGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawAngryGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawSadGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawSurprisedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawFocusedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawSkepticGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawUnimpressedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawWorriedGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawFuriousGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawSquintGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);
    void drawSuspiciousGeometry(int lx, int rx, int yL, int yR, int w, int hL, int hR, int r);

public:
    void init(lgfx::LGFX_Sprite* spriteBuffer);
    void render(const EyeModel& model);
};