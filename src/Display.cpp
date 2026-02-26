#include "Display.h"

// --- IMPORTANTE: Instanciação das variáveis estáticas ---
TFT_eSPI Display::tft = TFT_eSPI();
TFT_eSprite Display::canvas = TFT_eSprite(&tft);
uint32_t Display::corOlho = TFT_CYAN;

void Display::iniciar() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // Alocação do canvas na PSRAM
    canvas.setColorDepth(16); 
    if (canvas.createSprite(tft.width(), tft.height()) == NULL) {
        Serial.println("Erro ao alocar PSRAM!");
    }
    
    canvas.fillSprite(TFT_BLACK);
    renderizar();
}

void Display::renderizar() {
    // Agora o compilador sabe o que é 'canvas' e que ele pertence ao Display
    canvas.pushSprite(0, 0);
}

void Display::desenharOlhosAbertos() {
    canvas.fillSprite(TFT_BLACK);
    canvas.fillRoundRect(50, 70, 70, 100, 20, corOlho);  
    canvas.fillRoundRect(200, 70, 70, 100, 20, corOlho); 
    renderizar();
}

void Display::desenharOlhosFechados() {
    canvas.fillSprite(TFT_BLACK);
    canvas.fillRect(50, 120, 70, 15, corOlho);  
    canvas.fillRect(200, 120, 70, 15, corOlho); 
    renderizar();
}

void Display::piscar() {
    desenharOlhosFechados();
    delay(150); 
    desenharOlhosAbertos();
}