#include "Lights.h"

CRGB Lights::leds[NUM_LEDS];
uint8_t Lights::brilhoAtual = 0;
bool Lights::subindo = true;

bool Lights::iniciar() {
    if (NUM_LEDS <= 0) return false; // Fail-fast se mal configurado

    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    FastLED.clear(true);
    
    // Acende branco rápido para provar que o hardware de luz está vivo
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    delay(100);
    FastLED.clear(true);
    
    return true;
}

void Lights::atualizar(SystemState estadoAtual) {
    // A luz reage automaticamente ao humor/estado do sistema
    switch (estadoAtual) {
        case STATE_BOOTING:
            fill_solid(leds, NUM_LEDS, CRGB::Yellow);
            FastLED.show();
            break;
            
        case STATE_IDLE:
            respirar(CRGB::Cyan); // Modo passivo e amigável
            break;
            
        case STATE_CRITICAL_STOP:
            piscarAlarme(CRGB::Red); // Emergência total
            break;
            
        default:
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            break;
    }
}

void Lights::respirar(CRGB cor) {
    if (subindo) {
        brilhoAtual += 2;
        if (brilhoAtual >= 150) subindo = false;
    } else {
        brilhoAtual -= 2;
        if (brilhoAtual <= 10) subindo = true;
    }
    FastLED.setBrightness(brilhoAtual);
    fill_solid(leds, NUM_LEDS, cor);
    FastLED.show();
}

void Lights::piscarAlarme(CRGB cor) {
    // Pisca forte e rápido baseado no tempo (millis) sem usar delay()
    if ((millis() / 250) % 2 == 0) {
        fill_solid(leds, NUM_LEDS, cor);
    } else {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
    FastLED.setBrightness(255); // Brilho máximo para alerta
    FastLED.show();
}