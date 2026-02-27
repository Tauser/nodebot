#pragma once
#include <Arduino.h>
#include <SD_MMC.h>
#include "AudioFileSourceFS.h"
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
    static AudioFileSourceFS *file; 
    static AudioOutputI2S *out;
};