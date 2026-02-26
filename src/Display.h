#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../include/Config.h"

class Display {
public:
    static void iniciar();
    static void renderizar();
    
    // Funções de desenho
    static void desenharOlhosAbertos();
    static void desenharOlhosFechados();
    static void piscar();

private:
    static TFT_eSPI tft;
    static TFT_eSprite canvas; // O famoso 'canvas' que deu erro de undefined
    static uint32_t corOlho;   // A 'corOlho' que deu erro de undefined
};