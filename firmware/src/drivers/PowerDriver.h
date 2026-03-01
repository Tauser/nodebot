#pragma once
#include <stdint.h>

class PowerDriver {
public:
    void init(int adcPin);
    float readVoltage();

private:
    int _adcPin;
};