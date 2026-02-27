#include "AudioSys.h"
#include "SDSys.h" // Importamos o SD para podermos gravar logs de erro de áudio

AudioGeneratorMP3 *AudioSys::mp3 = nullptr;
AudioFileSourceSD *AudioSys::file = nullptr;
AudioOutputI2S *AudioSys::out = nullptr;

bool AudioSys::iniciar() {
    Serial.println("[SYSTEM] Iniciando AudioSys (SD/MP3)...");

    out = new AudioOutputI2S(0, 1);
    mp3 = new AudioGeneratorMP3();

    out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    out->SetGain(0.4); 

    Serial.println("[OK] AudioSys: Motor de Audio I2S online.");
    return true;
}

void AudioSys::tocar(const char* caminhoArquivo) {
    parar(); 

    file = new AudioFileSourceSD(caminhoArquivo);
    
    if (file->isOpen()) {
        mp3->begin(file, out);
        Serial.printf("[AUDIO] A reproduzir do SD: %s\n", caminhoArquivo);
    } else {
        Serial.printf("[ERRO] AudioSys: Ficheiro nao encontrado no SD: %s\n", caminhoArquivo);
        SDSys::gravarLog("ERRO DE AUDIO: Ficheiro em falta."); 
        delete file;
        file = nullptr;
    }
}

void AudioSys::parar() {
    if (mp3 && mp3->isRunning()) {
        mp3->stop();
    }
    if (file) {
        file->close();
        delete file;
        file = nullptr;
    }
}

void AudioSys::atualizar() {
    if (mp3 && mp3->isRunning()) {
        if (!mp3->loop()) {
            mp3->stop();
            parar(); 
        }
    }
}