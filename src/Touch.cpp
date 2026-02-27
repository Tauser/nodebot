#include "Touch.h" // (Altere para "Touch.h" se for esse o nome do seu ficheiro)
#include "Config.h"   // <--- Importa o Mapa Central

int TouchSys::consecutiveHits = 0;

bool TouchSys::iniciar() {
    int leituraInicial = touchRead(TOUCH_PIN);
    Serial.printf("[OK] TouchSys: Base capacitiva em %d\n", leituraInicial);
    return true;
}

bool TouchSys::lerTato() {

    int valorAtual = touchRead(TOUCH_PIN);
    
    if (valorAtual > TOUCH_CAPACITIVE_THRESHOLD) { 
        consecutiveHits++;
    } else {
        consecutiveHits = 0; 
    }

    return (consecutiveHits >= TOUCH_THRESHOLD_SAMPLES);
}