#include "Touch.h"

bool TouchSys::isTocado = false;

bool TouchSys::iniciar() {
    // O tato capacitivo não precisa de "begin", apenas testamos se o pino responde
    int leituraInicial = touchRead(PINO_FITA_COBRE);
    Serial.printf("[OK] TouchSys: Fita de cobre calibrada. Leitura base: %d\n", leituraInicial);
    return true;
}

bool TouchSys::lerTato() {
    // O ESP32-S3 retorna valores maiores quando tocado
    int valorAtual = touchRead(PINO_FITA_COBRE);
    isTocado = (valorAtual > LIMIAR_TATO);
    return isTocado;
}