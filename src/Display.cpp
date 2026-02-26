#include "Display.h"

TFT_eSPI Display::tft = TFT_eSPI();
uint32_t Display::corOlho = TFT_CYAN; // Cor padrão: Ciano

void Display::iniciar() {
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK);
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(MC_DATUM); 
    tft.drawString("NodeBot OS - Carregando Modulos...", tft.width() / 2, tft.height() / 2, 4);
    
    delay(2000); 
    desenharOlhosAbertos();
}

void Display::desenharOlhosAbertos() {
    tft.fillScreen(TFT_BLACK);
    tft.fillRoundRect(50, 70, 70, 100, 20, corOlho);  
    tft.fillRoundRect(200, 70, 70, 100, 20, corOlho); 
}

void Display::desenharOlhosFechados() {
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(50, 120, 70, 15, corOlho);  
    tft.fillRect(200, 120, 70, 15, corOlho); 
}

void Display::piscar() {
    desenharOlhosFechados();
    delay(150); 
    desenharOlhosAbertos();
}

void Display::desenharOlhosFelizes() {
    tft.fillScreen(TFT_BLACK);
    // Truque: Desenhamos dois círculos e cobrimos a metade de baixo com um retângulo preto
    // Isso cria aquele efeito de "arco" de quem está a sorrir com os olhos ( ^ ^ )
    tft.fillCircle(85, 120, 40, corOlho);
    tft.fillCircle(235, 120, 40, corOlho);
    tft.fillRect(40, 120, 240, 50, TFT_BLACK); 
}

void Display::desenharOlhosBravos() {
    tft.fillScreen(TFT_BLACK);
    // Base normal
    tft.fillRoundRect(50, 70, 70, 100, 20, corOlho);  
    tft.fillRoundRect(200, 70, 70, 100, 20, corOlho); 
    
    // Truque: Triângulos pretos por cima para "cortar" os cantos superiores internos ( > < )
    tft.fillTriangle(50, 50, 120, 50, 120, 100, TFT_BLACK);  // Sobrancelha esquerda
    tft.fillTriangle(200, 100, 200, 50, 270, 50, TFT_BLACK); // Sobrancelha direita
}

void Display::desenharOlhosTristes() {
    tft.fillScreen(TFT_BLACK);
    tft.fillRoundRect(50, 70, 70, 100, 20, corOlho);  
    tft.fillRoundRect(200, 70, 70, 100, 20, corOlho); 
    
    // Truque: Triângulos pretos para "cortar" os cantos superiores externos
    tft.fillTriangle(50, 100, 50, 50, 120, 50, TFT_BLACK);   // Esquerdo
    tft.fillTriangle(200, 50, 270, 50, 270, 100, TFT_BLACK); // Direito
}

void Display::desenharDormindo() {
    desenharOlhosFechados();
    
    // Adiciona o detalhe do "Zzz"
    tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    tft.drawString("Z", 250, 50, 4);
    tft.drawString("z", 270, 30, 2);
}