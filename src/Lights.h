#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "../include/Config.h"

class Lights {
public:
    static bool iniciar(); // Fail-Fast
    static void atualizar(SystemState estadoAtual); // Injeção de dependência do estado

private:
    static CRGB leds[NUM_LEDS];
    static uint8_t brilhoAtual;
    static bool subindo;
    
    // Animações internas
    static void respirar(CRGB cor);
    static void piscarAlarme(CRGB cor);
};