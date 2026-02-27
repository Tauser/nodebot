#include "Display.h"

TFT_eSPI Display::tft = TFT_eSPI();
Emocao Display::emocaoAtual = EMOCAO_NEUTRO;
Emocao Display::emocaoAnterior = EMOCAO_CANSADO; // Força a desenhar na primeira vez

bool Display::iniciar() {
    tft.init();
    tft.setRotation(1); // Paisagem
    tft.fillScreen(TFT_BLACK);
    Serial.println("[OK] Display: Inicializado em modo de alta velocidade.");
    return true;
}

void Display::definirEmocao(Emocao novaEmocao) {
    emocaoAtual = novaEmocao;
}

void Display::atualizar(SystemState state) {
    if (state == STATE_CRITICAL_STOP) {
        tft.fillScreen(TFT_RED);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("ERRO CRITICO", 80, 110, 4);
        return;
    }
    
    // VERIFICAÇÃO DE PERFORMANCE: Só gasta tempo a desenhar se a emoção mudar
    if (emocaoAtual != emocaoAnterior) {
        tft.fillScreen(TFT_BLACK); // Limpa o ecrã super rápido
        desenharRosto();
        emocaoAnterior = emocaoAtual; // Guarda o estado atual
    }
}

void Display::desenharRosto() {
    int cxEsq = 90;
    int cxDir = 230;
    int cy = 120;
    int raio = 45;
    
    // Desenho de primitivas diretas (O método mais confiável e rápido que existe)
    switch (emocaoAtual) {
        case EMOCAO_NEUTRO:
            tft.fillCircle(cxEsq, cy, raio, TFT_WHITE);
            tft.fillCircle(cxDir, cy, raio, TFT_WHITE);
            break;
            
        case EMOCAO_FELIZ:
            tft.fillCircle(cxEsq, cy, raio, TFT_GREEN);
            tft.fillCircle(cxDir, cy, raio, TFT_GREEN);
            // Apaga a metade inferior com um retângulo preto para fazer o "sorriso"
            tft.fillRect(cxEsq - 50, cy + 10, 100, 50, TFT_BLACK); 
            tft.fillRect(cxDir - 50, cy + 10, 100, 50, TFT_BLACK);
            break;
            
        case EMOCAO_ZANGADO:
            tft.fillCircle(cxEsq, cy, raio, TFT_RED);
            tft.fillCircle(cxDir, cy, raio, TFT_RED);
            // Corta o topo em diagonal para fazer a sobrancelha zangada
            tft.fillTriangle(cxEsq - 50, cy - 50, cxEsq + 50, cy - 10, cxEsq - 50, cy - 10, TFT_BLACK);
            tft.fillTriangle(cxDir - 50, cy - 10, cxDir + 50, cy - 50, cxDir + 50, cy - 10, TFT_BLACK);
            break;
            
        case EMOCAO_CANSADO:
            tft.fillCircle(cxEsq, cy, raio, TFT_DARKGREY);
            tft.fillCircle(cxDir, cy, raio, TFT_DARKGREY);
            // Corta a metade superior
            tft.fillRect(cxEsq - 50, cy - 50, 100, 50, TFT_BLACK); 
            tft.fillRect(cxDir - 50, cy - 50, 100, 50, TFT_BLACK);
            break;
    }
}