#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../include/Config.h"

class Display {
public:
    static bool iniciar();
    static void atualizar(SystemState state);
    static void definirEmocao(Emocao novaEmocao);

private:
    static TFT_eSPI tft;
    static Emocao emocaoAtual;
    static Emocao emocaoAnterior; 
    
    // Blink
    static unsigned long ultimoTempoPiscar;
    static int intervaloPiscar;
    static bool isPiscando;

    // Saccades
    static unsigned long ultimoTempoSaccade;
    static int intervaloSaccade;
    static int offsetOlharX;
    static int offsetOlharY;

    static void desenharRosto();
};