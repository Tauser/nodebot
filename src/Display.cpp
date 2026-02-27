#include "Display.h"

TFT_eSPI Display::tft = TFT_eSPI();
Emocao Display::emocaoAtual = EMOCAO_NEUTRO;
Emocao Display::emocaoAnterior = EMOCAO_CANSADO; 

// Relógios Biológicos
unsigned long Display::ultimoTempoPiscar = 0;
int Display::intervaloPiscar = 3000;
bool Display::isPiscando = false;

// Saccades (Micromovimentos Oculares)
unsigned long Display::ultimoTempoSaccade = 0;
int Display::intervaloSaccade = 1000;
int Display::offsetOlharX = 0;
int Display::offsetOlharY = 0;

bool Display::iniciar() {
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK);
    return true;
}

void Display::definirEmocao(Emocao novaEmocao) {
    emocaoAtual = novaEmocao;
}

void Display::atualizar(SystemState state) {
    if (state == STATE_CRITICAL_STOP || state == STATE_SLEEPING) return;

    bool precisaRedesenhar = false;
    unsigned long tempoAtual = millis();

    // 1. Lógica de Saccades (Os olhos procuram alvos aleatórios)
    if (!isPiscando && (tempoAtual - ultimoTempoSaccade > intervaloSaccade)) {
        ultimoTempoSaccade = tempoAtual;
        intervaloSaccade = random(800, 2500); // Salta o olhar entre 0.8s e 2.5s
        
        // Deslocamento máximo de 15 pixeis para não parecer estrábico
        offsetOlharX = random(-15, 16); 
        offsetOlharY = random(-10, 11);
        precisaRedesenhar = true;
    }

    // 2. Lógica de Piscar
    if (!isPiscando && (tempoAtual - ultimoTempoPiscar > intervaloPiscar)) {
        isPiscando = true;
        ultimoTempoPiscar = tempoAtual;
        precisaRedesenhar = true;
    } 
    else if (isPiscando && (tempoAtual - ultimoTempoPiscar > 150)) { 
        isPiscando = false;
        ultimoTempoPiscar = tempoAtual;
        intervaloPiscar = random(2000, 6000); 
        precisaRedesenhar = true;
    }

    if (emocaoAtual != emocaoAnterior) {
        precisaRedesenhar = true;
        emocaoAnterior = emocaoAtual;
    }

    if (precisaRedesenhar) {
        tft.fillScreen(TFT_BLACK);
        desenharRosto();
    }
}

void Display::desenharRosto() {
    // Adicionamos o Offset (Saccade) à posição central nativa
    int cxEsq = 90 + offsetOlharX;
    int cxDir = 230 + offsetOlharX;
    int cy = 120 + offsetOlharY;
    int raio = 45;

    if (isPiscando) {
        tft.fillRect(cxEsq - raio, cy - 5, raio * 2, 10, TFT_WHITE);
        tft.fillRect(cxDir - raio, cy - 5, raio * 2, 10, TFT_WHITE);
        return; 
    }
    
    // Desenho procedural rápido com as novas coordenadas vivas
    switch (emocaoAtual) {
        case EMOCAO_NEUTRO:
            tft.fillCircle(cxEsq, cy, raio, TFT_WHITE);
            tft.fillCircle(cxDir, cy, raio, TFT_WHITE);
            break;
            
        case EMOCAO_FELIZ:
            tft.fillCircle(cxEsq, cy, raio, TFT_GREEN);
            tft.fillCircle(cxDir, cy, raio, TFT_GREEN);
            tft.fillRect(cxEsq - 50, cy + 10, 100, 50, TFT_BLACK); 
            tft.fillRect(cxDir - 50, cy + 10, 100, 50, TFT_BLACK);
            break;
            
        case EMOCAO_ZANGADO:
            tft.fillCircle(cxEsq, cy, raio, TFT_RED);
            tft.fillCircle(cxDir, cy, raio, TFT_RED);
            tft.fillTriangle(cxEsq - 50, cy - 50, cxEsq + 50, cy - 10, cxEsq - 50, cy - 10, TFT_BLACK);
            tft.fillTriangle(cxDir - 50, cy - 10, cxDir + 50, cy - 50, cxDir + 50, cy - 10, TFT_BLACK);
            break;
            
        case EMOCAO_CANSADO:
            tft.fillCircle(cxEsq, cy, raio, TFT_DARKGREY);
            tft.fillCircle(cxDir, cy, raio, TFT_DARKGREY);
            tft.fillRect(cxEsq - 50, cy - 50, 100, 50, TFT_BLACK); 
            tft.fillRect(cxDir - 50, cy - 50, 100, 50, TFT_BLACK);
            break;
    }
}