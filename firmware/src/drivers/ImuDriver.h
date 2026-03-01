#pragma once
#include <stdint.h>

struct ImuData {
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float temperature;
};

class ImuDriver
{
public:
    bool init(int sdaPin, int sclPin);
    bool readData(ImuData& outData);

private:
    bool _isInitialized;
    const uint8_t MPU6050_ADDR = 0x68; 
};