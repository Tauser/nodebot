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
    static Emocao emocaoAnterior; // Para garantir que só redesenha quando necessário!
    static void desenharRosto();
};