#include "ImuDriver.h"
#include <Wire.h>
#include <Arduino.h>

bool ImuDriver::init(int sdaPin, int sclPin)
{
    Wire.begin(sdaPin, sclPin);
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0) {
        _isInitialized = false;
        return false;
    }
    _isInitialized = true;
    return true;
}

bool ImuDriver::readData(ImuData& outData)
{
    if (!_isInitialized) return false;

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    if (Wire.endTransmission(false) != 0) return false;

    Wire.requestFrom((uint16_t)MPU6050_ADDR, (uint8_t)14, (uint8_t)true);
    
    if (Wire.available() == 14) {

        int16_t ax = (Wire.read() << 8 | Wire.read());
        int16_t ay = (Wire.read() << 8 | Wire.read());
        int16_t az = (Wire.read() << 8 | Wire.read());
        int16_t temp = (Wire.read() << 8 | Wire.read());
        int16_t gx = (Wire.read() << 8 | Wire.read());
        int16_t gy = (Wire.read() << 8 | Wire.read());
        int16_t gz = (Wire.read() << 8 | Wire.read());

        outData.accelX = ax / 16384.0f;
        outData.accelY = ay / 16384.0f;
        outData.accelZ = az / 16384.0f;
        outData.temperature = (temp / 340.0f) + 36.53f;
        outData.gyroX = gx / 131.0f;
        outData.gyroY = gy / 131.0f;
        outData.gyroZ = gz / 131.0f;
        
        return true;
    }
    return false;
}