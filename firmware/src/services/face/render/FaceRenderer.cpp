#include "FaceRenderer.h"
#include "core/config/hardware_config.h" // Garanta que o caminho bate certo com a sua pasta src

void FaceRenderer::init() {
    // Agora sim, usando a sua estrutura de hardware perfeitamente encapsulada!
    _display.init();
    
    _display.clearScreen(0x0000); // ÚNICA vez que limpamos tudo!
    
    // Inicializa o Buffer de Memória (Double Buffer)
    // Criamos uma faixa de 320x160 que cobre toda a área de movimento dos olhos.
    if (_canvas) delete _canvas;
    _canvas = new GFXcanvas16(320, 160);
    
    // Inicializa o estado visual
    _current.pupilX = 0;
    _current.pupilY = 0;
    _current.pupilSize = 1.0;
    _current.lidOpen = 1.0;
}

void FaceRenderer::render(const EyeModel& eye) {
    if (!_canvas) return;

    // 1. Limpa o CANVAS (Memória rápida)
    _canvas->fillScreen(0x0000);

    // 2. FÍSICA VISUAL (Suavização / Lerp)
    // Movemos o estado visual (_current) 20% em direção ao alvo (eye.get()) a cada frame.
    // Isso cria um movimento orgânico e elástico.
    float smoothFactor = 0.25f; // Ajuste: 0.1 (Lento/Pesado) a 0.5 (Rápido/Agitado)
    
    _current.pupilX += (eye.get().pupilX - _current.pupilX) * smoothFactor;
    _current.pupilY += (eye.get().pupilY - _current.pupilY) * smoothFactor;
    _current.pupilSize += (eye.get().pupilSize - _current.pupilSize) * smoothFactor;
    _current.lidOpen = eye.get().lidOpen; // O piscar deve ser instantâneo (controlado pela Animation)

    // Calcula tamanho
    int baseWidth = 80 * _current.pupilSize;  // Olhos mais largos e expressivos
    int baseHeight = 90 * _current.pupilSize;
    int actualHeight = baseHeight * _current.lidOpen; 

    if (actualHeight <= 2) return; // Olho fechado

    // Calcula posição no ecrã (offset do Saccade * 50 pixels de amplitude)
    int leftEyeCenterX = 80 + (_current.pupilX * 40);
    int rightEyeCenterX = 240 + (_current.pupilX * 40);
    int eyeCenterY = 120 + (_current.pupilY * 40);
    
    // Coordenadas finais de desenho (Top-Left)
    int lx = leftEyeCenterX - (baseWidth / 2);
    int rx = rightEyeCenterX - (baseWidth / 2);
    int y  = eyeCenterY - (actualHeight / 2);

    // Ajuste de Coordenadas para o Canvas
    // O Canvas começa no Y=40 do ecrã real, então subtraímos 40.
    int canvasY = y - 40;
    int pupilSize = baseWidth / 3.5; // Tamanho da pupila proporcional ao olho

    // 3. DESENHO ORGÂNICO
    uint16_t eyeColor = 0xFFFF; // Branco
    
    // Olho Esquerdo
    _canvas->fillRoundRect(lx, canvasY, baseWidth, actualHeight, 20, eyeColor);
    // Pupila Esquerda (Preta)
    _canvas->fillCircle(lx + baseWidth/2, canvasY + actualHeight/2, pupilSize, 0x0000);

    // Olho Direito
    _canvas->fillRoundRect(rx, canvasY, baseWidth, actualHeight, 20, eyeColor);
    // Pupila Direita (Preta)
    _canvas->fillCircle(rx + baseWidth/2, canvasY + actualHeight/2, pupilSize, 0x0000);
    
    // 4. PUSH FINAL (O Segredo)
    // Envia o buffer para o ecrã
    _display.pushImage(0, 40, 320, 160, _canvas->getBuffer());
}