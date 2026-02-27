#pragma once
#include <Arduino.h>
#include "AudioFileSourceSD.h"   
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class AudioSys {
public:
    static bool iniciar();
    static void atualizar();
    static void tocar(const char* caminhoArquivo);
    static void parar();

private:
    static AudioGeneratorMP3 *mp3;
    static AudioFileSourceSD *file; // <--- MUDANÇA: Ponteiro para o SD
    static AudioOutputI2S *out;

    // PINOUT DO AMPLIFICADOR I2S (MAX98357A)
    static const int I2S_BCLK = 5; 
    static const int I2S_LRC  = 6; 
    static const int I2S_DOUT = 7; 
};