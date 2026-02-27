#include "Touch.h"

int TouchSys::consecutiveHits = 0;

bool TouchSys::iniciar() {
    int leituraInicial = touchRead(PINO_FITA_COBRE);
    Serial.printf("[OK] TouchSys: Base capacitiva em %d\n", leituraInicial);
    return true;
}

bool TouchSys::lerTato() {
    int valorAtual = touchRead(PINO_FITA_COBRE);
    
    if (valorAtual > LIMIAR_CAPACITIVO) { 
        consecutiveHits++;
    } else {
        consecutiveHits = 0; 
    }

    return (consecutiveHits >= TOUCH_THRESHOLD_SAMPLES);
}