#pragma once
#include <stdint.h>
#include "drivers/PowerDriver.h" // <-- NOVO: Importa o Driver

class PowerService {
public:
    void init();
    void update(); 

    float getVoltage() const;
    uint8_t getBatteryPercentage() const;

private:
    PowerDriver _driver; // <-- NOVO: A instância do Driver
    uint32_t _lastCheckMs;
    float _currentVoltage;
    uint8_t _batteryPercentage;
    bool _lowBatteryAlertSent;
};