#pragma once
#include <stdint.h>

class ServoDriver
{
public:
    void init(int rxPin, int txPin, uint32_t baudRate);
    void setAngle(uint8_t servoId, uint16_t angle);
    uint16_t getAngle(uint8_t servoId) const;

private:
    int _rxPin;
    int _txPin;
    uint32_t _baudRate;
    uint16_t _currentAngleHead; 
    uint16_t _currentAngleEyes;
    
    void sendSerialCommand(uint8_t id, uint16_t position);
};