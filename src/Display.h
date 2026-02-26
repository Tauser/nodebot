#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../include/Config.h"

class Display {
public:
    static void iniciar();
    
    // O repertório completo de emoções do NodeBot
    static void desenharOlhosAbertos();
    static void desenharOlhosFechados();
    static void piscar();
    static void desenharOlhosFelizes();
    static void desenharOlhosBravos();
    static void desenharOlhosTristes();
    static void desenharDormindo();

private:
    static TFT_eSPI tft;
    // Variável para a cor dos olhos (facilita se quisermos mudar a cor depois)
    static uint32_t corOlho; 
};