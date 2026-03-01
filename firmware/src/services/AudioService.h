#pragma once
#include <stdint.h>
#include "drivers/AudioDriver.h"

// --- NOVO: Integração com a IA e Sistema Nervoso ---
#include "ai/LocalClassifier.h"
#include "core/EventBus.h"

enum class SoundType {
    BEEP_SUCCESS,
    BEEP_ERROR,
    WAKE_WORD_DETECTED,
    SYSTEM_READY
};

class AudioService
{
public:
    void init();
    void update(); // NOVO: Loop para o microfone ficar sempre a ouvir

    void playSystemSound(SoundType type);
    void playRawStream(const uint8_t* audioData, size_t length);
    void stopAll();
    void setVolume(uint8_t percentage);

private:
    AudioDriver _audioDriver;
    LocalClassifier _classifier; // NOVO: O Cérebro Tradutor
    uint8_t _currentVolume;
    
    void generateTone(uint16_t frequency, uint16_t durationMs);
    float lerMicrofoneI2S(); // NOVO: Lê os dados crus do microfone
};