#include "AudioSys.h"
#include "SDSys.h"
#include "Config.h"

AudioGeneratorMP3 *AudioSys::mp3 = nullptr;
AudioFileSourceFS *AudioSys::file = nullptr; // <--- MUDANÇA
AudioOutputI2S *AudioSys::out = nullptr;

bool AudioSys::iniciar() {
    Serial.println("[SYSTEM] Iniciando AudioSys (SD_MMC/MP3)...");

    out = new AudioOutputI2S(0, 1);
    mp3 = new AudioGeneratorMP3();

    // Usando as variáveis do Config.h
    out->SetPinout(I2S_BCLK_PIN, I2S_LRC_PIN, I2S_DOUT_PIN);
    out->SetGain(0.4); 

    Serial.println("[OK] AudioSys: Motor de Audio I2S online.");
    return true;
}

void AudioSys::tocar(const char* caminhoArquivo) {
    parar(); 

    // <--- MUDANÇA: Passamos o sistema SD_MMC como parâmetro para o áudio!
    file = new AudioFileSourceFS(SD_MMC, caminhoArquivo);
    
    if (file->isOpen()) {
        mp3->begin(file, out);
        Serial.printf("[AUDIO] A reproduzir do SD: %s\n", caminhoArquivo);
    } else {
        Serial.printf("[ERRO] AudioSys: Ficheiro nao encontrado no SD_MMC: %s\n", caminhoArquivo);
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