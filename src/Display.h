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
    
    // Relógio Biológico (Blink)
    static unsigned long ultimoTempoPiscar;
    static int intervaloPiscar;
    static bool isPiscando;

    // Relógio Biológico (Saccades) -> Faltava declarar isto!
    static unsigned long ultimoTempoSaccade;
    static int intervaloSaccade;
    static int offsetOlharX;
    static int offsetOlharY;

    static void desenharRosto();
};