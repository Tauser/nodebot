#include "ServoDriver.h"
#include "core/config/hardware_config.h"
#include <Arduino.h>

void ServoDriver::init(int rxPin, int txPin, uint32_t baudRate)
{
    _rxPin = rxPin;
    _txPin = txPin;
    _baudRate = baudRate;
    _currentAngleHead = 2048; 
    _currentAngleEyes = 2048;

    // Inicializa a Hardware Serial 1 para falar com os motores
    Serial1.begin(_baudRate, SERIAL_8N1, _rxPin, _txPin);
}

void ServoDriver::setAngle(uint8_t servoId, uint16_t angle)
{
    if (servoId == Hardware::Servo::ID_HEAD_PAN) {
        _currentAngleHead = angle;
    } else if (servoId == Hardware::Servo::ID_HEAD_TILT) {
        _currentAngleEyes = angle;
    }
    sendSerialCommand(servoId, angle);
}

uint16_t ServoDriver::getAngle(uint8_t servoId) const
{
    if (servoId == Hardware::Servo::ID_HEAD_PAN) return _currentAngleHead;
    if (servoId == Hardware::Servo::ID_HEAD_TILT) return _currentAngleEyes;
    return 0;
}

void ServoDriver::sendSerialCommand(uint8_t id, uint16_t position)
{
    byte message[7];
    message[0] = 0xFF; 
    message[1] = 0xFF; 
    message[2] = id;   
    message[3] = 0x04; 
    message[4] = 0x03; 
    message[5] = position & 0xFF; 
    message[6] = (position >> 8) & 0xFF; 
    
    Serial1.write(message, sizeof(message));
}