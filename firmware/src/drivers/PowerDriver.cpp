#include "PowerDriver.h"
#include <Arduino.h>

void PowerDriver::init(int adcPin) {
    _adcPin = adcPin;
    // O ESP32-S3 precisa que o pino ADC seja configurado como entrada
    pinMode(_adcPin, INPUT);
}

float PowerDriver::readVoltage() {
    int rawValue = analogRead(_adcPin);
    // Matemática de conversão do ADC do ESP32 para Volts (assumindo divisor de tensão na placa)
    return (rawValue / 4095.0f) * 3.3f * 2.0f; 
}