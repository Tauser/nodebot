#include "Display.h"
#include <qrcode.h>

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

// QR Code
bool Display::exibindoQR = false;
String Display::textoQR = "";

bool Display::iniciar() {
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK);
    Serial.println("[OK] Display: Motor Procedural com Saccades e QR online.");
    return true;
}

void Display::definirEmocao(Emocao novaEmocao) {
    emocaoAtual = novaEmocao;
}

void Display::atualizar(SystemState state) {
    // 1. Se estiver a mostrar QR Code, congela os olhos
    if (exibindoQR) return;

    if (state == STATE_CRITICAL_STOP) {
        tft.fillScreen(TFT_RED);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("ERRO CRITICO", 80, 110, 4);
        return;
    }
    if (state == STATE_SLEEPING) {
        tft.fillScreen(TFT_BLACK);
        return;
    }

    bool precisaRedesenhar = false;
    unsigned long tempoAtual = millis();

    // 2. Lógica de Saccades
    if (!isPiscando && (tempoAtual - ultimoTempoSaccade > intervaloSaccade)) {
        ultimoTempoSaccade = tempoAtual;
        intervaloSaccade = random(800, 2500); 
        offsetOlharX = random(-15, 16); 
        offsetOlharY = random(-10, 11);
        precisaRedesenhar = true;
    }

    // 3. Lógica de Piscar
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

    // 4. Lógica de Mudança de Emoção
    if (emocaoAtual != emocaoAnterior) {
        precisaRedesenhar = true;
        emocaoAnterior = emocaoAtual;
    }

    // 5. Renderização
    if (precisaRedesenhar) {
        tft.fillScreen(TFT_BLACK);
        desenharRosto();
    }
}

void Display::desenharRosto() {
    int cxEsq = 90 + offsetOlharX;
    int cxDir = 230 + offsetOlharX;
    int cy = 120 + offsetOlharY;
    int raio = 45;

    if (isPiscando) {
        tft.fillRect(cxEsq - raio, cy - 5, raio * 2, 10, TFT_WHITE);
        tft.fillRect(cxDir - raio, cy - 5, raio * 2, 10, TFT_WHITE);
        return; 
    }
    
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

// ==========================================
// MÉTODOS DO QR CODE
// ==========================================
void Display::ativarQR(String texto) {
    textoQR = texto;
    exibindoQR = true;
    emocaoAnterior = EMOCAO_CANSADO; 
    tft.fillScreen(TFT_WHITE);       
    desenharQR();
}

void Display::desativarQR() {
    exibindoQR = false;
    tft.fillScreen(TFT_BLACK);
}

void Display::desenharQR() {
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    qrcode_initText(&qrcode, qrcodeData, 3, 0, textoQR.c_str());

    int scale = 5; 
    int offsetX = (320 - (qrcode.size * scale)) / 2; 
    int offsetY = (240 - (qrcode.size * scale)) / 2;

    for (uint8_t y = 0; y < qrcode.size; y++) {
        for (uint8_t x = 0; x < qrcode.size; x++) {
            if (qrcode_getModule(&qrcode, x, y)) {
                tft.fillRect(offsetX + (x * scale), offsetY + (y * scale), scale, scale, TFT_BLACK);
            }
        }
    }
}