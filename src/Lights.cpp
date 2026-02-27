#include "Lights.h"

unsigned long Lights::ultimoPisca = 0;
bool Lights::estadoLed = false;

bool Lights::iniciar() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Nasce desligado
    Serial.println("[SYSTEM] Modulo de Luzes online.");
    return true;
}

void Lights::atualizar(SystemState state) {
    unsigned long tempoAtual = millis();
    int intervalo = 0;

    // A cadência do coração depende do estado emocional/sistema do robô
    switch(state) {
        case STATE_BOOTING: 
            intervalo = 150; // A acordar
            break;
        case STATE_IDLE: 
            intervalo = 1000; // Calmo, batimento lento
            break; 
        case STATE_INTERACTING: 
            intervalo = 200; // Entusiasmado a executar uma ação
            break;
        case STATE_CRITICAL_STOP: 
            intervalo = 50; // Pânico, erro no sistema (pisca como louco)
            break;
        default: 
            intervalo = 500; 
            break;
    }

    // Comuta o estado do LED sem usar NENHUM delay() que trave o Cérebro
    if (tempoAtual - ultimoPisca > intervalo) {
        ultimoPisca = tempoAtual;
        estadoLed = !estadoLed;
        digitalWrite(LED_PIN, estadoLed ? HIGH : LOW);
    }
}