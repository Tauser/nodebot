#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../include/Config.h"

// O catálogo de sentimentos do NodeBot
enum RobotEmotion {
    EMOCAO_NEUTRO,
    EMOCAO_FELIZ,
    EMOCAO_ZANGADO,
    EMOCAO_TRISTE,
    EMOCAO_CANSADO
};

class Display {
public:
    static bool iniciar(); // Mantém o Fail-Fast
    static void atualizar(SystemState estadoAtual);
    static void definirEmocao(RobotEmotion novaEmocao); // Injetor de personalidade

private:
    static TFT_eSPI tft;
    static TFT_eSprite canvas;
    static unsigned long proximoPiscar;
    static RobotEmotion emocaoAtual;
    static bool isPiscando;

    // A Geometria Base (Evita Magic Numbers espalhados pelo código)
    static const int OLHO_LARGURA = 70;
    static const int OLHO_ALTURA = 100;
    static const int RAIO_CURVATURA = 20;
    static const int POS_Y = 70;
    static const int POS_X_ESQ = 50;
    static const int POS_X_DIR = 200;

    // Motor Procedural
    static void desenharOlhoBase(int x, int y, uint32_t cor);
    static void aplicarMascara(int x, int y, RobotEmotion emocao, bool olhoEsquerdo);
    static void renderizar();
};