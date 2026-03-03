#include "FaceService.h"

void FaceService::begin(DisplayDriver& driver) {
    _tft = driver.getLGFX();
    
    // SOLUÇÃO 4: Usar 16 bits de cor (Reduz tráfego de dados em 33% vs 24 bits)
    canvas.setColorDepth(16);

    // Voltamos para a PSRAM para garantir que o buffer de vídeo tenha um espaço seguro e isolado.
    canvas.setPsram(true);
    canvas.createSprite(240, 240);
    
    // INICIALIZAÇÃO CRÍTICA PARA AS ANIMAÇÕES FUNCIONAREM
    model.blinkState = BlinkState::EYE_OPEN;
    model.blinkFactor = 1.0f;
    model.blinkInterval = 3000; // Começa com 3 segundos
    model.currentSaccadeX = 0;
    model.currentSaccadeY = 0;
    
    renderer.init(&canvas);
    setExpression(Expression::NEUTRAL);
}

void FaceService::update() {
    // Se o animator.update travar aqui, o log do blinkFactor nunca muda
    animator.update(model); 
    
    renderer.render(model);
    
    // CORREÇÃO DE POSICIONAMENTO:
    // A tela está em modo retrato (240 de largura por 320 de altura).
    // O rosto é um quadrado de 240x240. Para centralizá-lo, o x deve ser 0 e o y deve ser (320 - 240) / 2 = 40.
    canvas.pushSprite(_tft, 0, 40); 
}

// ==========================================
// O SEU setExpression CONTINUA EXATAMENTE IGUAL
// ==========================================
void FaceService::setExpression(Expression expr) {
    model.currentExpression = expr;
    
    model.baseWidth = 80; 
    model.baseHeight = 80; 
    model.baseRadius = 16; 
    model.blinkInterval = 4000;

    switch (expr) {
        case Expression::NEUTRAL:
            break;
        case Expression::HAPPY:
            model.blinkInterval = 3000;
            break;
        case Expression::ANGRY: 
            model.baseRadius = 10;
            model.blinkInterval = 6000;
            break;
        case Expression::SAD: 
            model.baseWidth = 70;
            model.baseHeight = 70; 
            model.blinkInterval = 5000;
            break;
        case Expression::SURPRISED: 
            model.baseWidth = 96;
            model.baseHeight = 96; 
            model.baseRadius = 32;
            model.blinkInterval = 10000;
            break;
        case Expression::FOCUSED:
            model.blinkInterval = 8000; 
            break;
        case Expression::SKEPTIC:
            model.blinkInterval = 5000;
            break;
        case Expression::UNIMPRESSED:
            model.blinkInterval = 6000;
            break;
        case Expression::WORRIED:
            model.blinkInterval = 2500;
            break;
        case Expression::FURIOUS: 
            model.baseHeight = 70;
            model.baseRadius = 10;
            model.blinkInterval = 7000; 
            break;
        case Expression::SQUINT: 
            model.baseHeight = 60;
            model.blinkInterval = 5000; 
            break;
        case Expression::SUSPICIOUS:
            model.blinkInterval = 6000;
            break;
    }
}