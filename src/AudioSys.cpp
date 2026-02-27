#include "AudioSys.h"

Audio AudioSys::audio;

bool AudioSys::iniciar() {
    // Pinos I2S do amplificador MAX98357A
    // Vamos usar pinos seguros do ESP32-S3 (Ajuste depois no Config.h se precisar)
    audio.setPinout(11, 10, 12); 
    audio.setVolume(15); // Volume de 0 a 21
    
    Serial.println("[OK] AudioSys: Amplificador I2S configurado.");
    return true; 
}

void AudioSys::atualizar() {
    audio.loop(); 
}