#include "AudioService.h"
#include "core/config/hardware_config.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <math.h>

void AudioService::init()
{
    _audioDriver.init(
        Hardware::AudioOut::PIN_BCLK,
        Hardware::AudioOut::PIN_LRCK,
        Hardware::AudioOut::PIN_DATA,
        Hardware::AudioOut::SAMPLE_RATE
    );
    
    setVolume(70); 
}

void AudioService::update()
{
    float volumeBruto = lerMicrofoneI2S(); 
    EventType intencaoDetectada;
    
    // Pergunta à IA se o barulho detetado significa algo
    if (_classifier.classifyAudio(volumeBruto, intencaoDetectada)) {
        
        if (intencaoDetectada == EventType::LOUD_NOISE) {
            // Grita para o Cérebro: "Barulho Assustador!"
            Bus.publish(SystemEvent::LOUD_NOISE, volumeBruto);
        }
        else if (intencaoDetectada == EventType::INTERACTION_POSITIVE) {
            // Alguém falou normalmente, considera uma interação
            Bus.publish(SystemEvent::TOUCH_TAP, volumeBruto); 
        }
    }
}

float AudioService::lerMicrofoneI2S()
{
    // PLACEHOLDER: Aqui no futuro o driver vai ler o pino I2S_DATA 
    // e retornar o volume RMS (Root Mean Square) entre 0.0 e 1.0.
    return 0.1f; // Silêncio base simulado
}

void AudioService::setVolume(uint8_t percentage)
{
    if (percentage > 100) percentage = 100;
    _currentVolume = percentage;
    _audioDriver.setVolume(percentage); 
}

void AudioService::stopAll()
{
    _audioDriver.clearBuffer();
}

void AudioService::playSystemSound(SoundType type)
{
    
    switch (type) {
        case SoundType::BEEP_SUCCESS:
            generateTone(1000, 100); 
            vTaskDelay(pdMS_TO_TICKS(50));
            generateTone(1500, 150); 
            break;
            
        case SoundType::BEEP_ERROR:
            generateTone(300, 300); 
            break;
            
        case SoundType::WAKE_WORD_DETECTED:
            generateTone(800, 50);
            vTaskDelay(pdMS_TO_TICKS(50));
            generateTone(1200, 100);
            break;
            
        case SoundType::SYSTEM_READY:
            generateTone(523, 150); 
            generateTone(659, 150); 
            generateTone(783, 200); 
            break;
    }
}

void AudioService::playRawStream(const uint8_t* audioData, size_t length)
{
    // Usado quando a IA (CloudService) devolver o áudio gerado.
    // O Service apenas empurra para o driver limitando pelo volume.
    _audioDriver.writeBuffer(audioData, length);
}

void AudioService::generateTone(uint16_t frequency, uint16_t durationMs)
{
    // Aqui a matemática de áudio vira bytes crus e desce para o Driver.
    // (Omitindo a matemática do seno para manter legível, mas o conceito é:
    //  criar array de 16bits e chamar _audioDriver.writeBuffer() )
}

