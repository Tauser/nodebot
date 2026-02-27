#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "../include/Config.h"

class Lights {
public:
    static bool iniciar();
    static void atualizar(SystemState estadoAtual);

private:
    static CRGB leds[NUM_LEDS];
    static uint8_t brilhoAtual;
    static bool subindo;
    
    // Animações
    static void respirar(CRGB cor);
    static void piscarAlarme(CRGB cor);
};