#include "AudioService.h"
#include <Arduino.h>
#include "../ai/LocalClassifier.h" // Garante que o tipo EventType é conhecido

void AudioService::init() {
    // Inicializa driver de áudio
}

void AudioService::update() {
    // Simulação de leitura
    float volumeBruto = 0.0f; 
    _currentVolume = volumeBruto;

    EventType intencaoDetectada;
    if (_classifier.classifyAudio(volumeBruto, intencaoDetectada)) {
        if (intencaoDetectada == EventType::LOUD_NOISE) {
            // Notificar sistema
            // Serial.println("Barulho detetado!");
        }
    }
}

float AudioService::getVolume() const {
    return _currentVolume;
}