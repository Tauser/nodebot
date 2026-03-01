#include "PowerService.h"
#include "core/config/hardware_config.h"
#include "core/EventBus.h"
#include <Arduino.h>

void PowerService::init() {
    // 1. Inicializa o hardware através do Driver (usando o pino do seu mapa)
    _driver.init(Hardware::Sensors::PIN_BATTERY_ADC);
    
    _lastCheckMs = 0;
    _currentVoltage = 4.2f; // Assume bateria cheia no arranque
    _batteryPercentage = 100;
    _lowBatteryAlertSent = false;
}

void PowerService::update() {
    uint32_t now = millis();
    
    // Só verifica a bateria a cada 10 segundos para não gastar CPU
    if (now - _lastCheckMs < 10000) return;
    _lastCheckMs = now;

    // 2. Lê a voltagem real através do Driver! (Sem tocar no Arduino.h diretamente)
    _currentVoltage = _driver.readVoltage();

    // Matemática de limites da Lipo
    const float MAX_V = 4.2f;
    const float MIN_V = 3.2f;

    if (_currentVoltage >= MAX_V) {
        _batteryPercentage = 100;
    } else if (_currentVoltage <= MIN_V) {
        _batteryPercentage = 0;
    } else {
        _batteryPercentage = (uint8_t)(((_currentVoltage - MIN_V) / (MAX_V - MIN_V)) * 100.0f);
    }

    // 3. O Serviço toma a decisão lógica (Avisa o Cérebro)
    if (_batteryPercentage < 15 && !_lowBatteryAlertSent) {
        Bus.publish(SystemEvent::BATTERY_LOW, _batteryPercentage);
        _lowBatteryAlertSent = true;
    } 
    // Se a voltagem subir (conectou o cabo), reseta o alarme
    else if (_batteryPercentage > 20) {
        _lowBatteryAlertSent = false;
    }
}

float PowerService::getVoltage() const { return _currentVoltage; }
uint8_t PowerService::getBatteryPercentage() const { return _batteryPercentage; }