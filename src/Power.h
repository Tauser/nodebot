#pragma once
#include <Arduino.h>
#include "../include/Config.h"

class Power {
public:
    static bool iniciar(); // Fail-Fast
    static void monitorar(); // Função rodada pela TaskTelemetry

private:
    static const int NUM_LEITURAS = 10;
    static int leituras[NUM_LEITURAS];
    static int indice;
    static long total;
    
    static const float TENSAO_MAXIMA; 
    static const float TENSAO_MINIMA; 

    static int lerPorcentagem();
};