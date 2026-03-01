#include "MotionService.h"
#include "core/config/hardware_config.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void MotionService::init()
{
    // O Service pega na configuração física e passa para o Driver.
    _servoDriver.init(
        Hardware::Servo::PIN_RX, 
        Hardware::Servo::PIN_TX, 
        Hardware::Servo::BAUD_RATE
    );
    _isMoving = false;
    
    lookCenter(); // Acorda a olhar em frente
}

void MotionService::lookCenter()
{
    // 2048 é o centro absoluto nos servos Feetech/STS (0 a 4096)
    setHeadPosition(2048, 2048);
}

void MotionService::lookLeft()
{
    // Move o PAN, mantém o TILT onde estava
    uint16_t currentTilt = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_TILT);
    setHeadPosition(2500, currentTilt); 
}

void MotionService::lookRight()
{
    uint16_t currentTilt = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_TILT);
    setHeadPosition(1500, currentTilt);
}

void MotionService::lookUp()
{
    uint16_t currentPan = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_PAN);
    setHeadPosition(currentPan, 1800);
}

void MotionService::lookDown()
{
    uint16_t currentPan = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_PAN);
    setHeadPosition(currentPan, 2300);
}

void MotionService::nod()
{
    if (_isMoving) return; // Evita sobreposição de comandos
    _isMoving = true;
    
    uint16_t currentPan = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_PAN);
    
    setHeadPosition(currentPan, 2300); // Abaixa a cabeça
    vTaskDelay(pdMS_TO_TICKS(200));
    setHeadPosition(currentPan, 1800); // Levanta a cabeça
    vTaskDelay(pdMS_TO_TICKS(200));
    lookCenter();                      // Volta à pose natural
    
    _isMoving = false;
}

void MotionService::shake()
{
    if (_isMoving) return;
    _isMoving = true;
    
    uint16_t currentTilt = _servoDriver.getAngle(Hardware::Servo::ID_HEAD_TILT);
    
    setHeadPosition(2500, currentTilt); // Olha esquerda
    vTaskDelay(pdMS_TO_TICKS(200));
    setHeadPosition(1500, currentTilt); // Olha direita
    vTaskDelay(pdMS_TO_TICKS(300));
    lookCenter();                       // Centro
    
    _isMoving = false;
}

void MotionService::setHeadPosition(uint16_t pan, uint16_t tilt)
{
    // O Service faz o mapeamento das "Intenções" para os IDs físicos do motor
    _servoDriver.setAngle(Hardware::Servo::ID_HEAD_PAN, pan);
    _servoDriver.setAngle(Hardware::Servo::ID_HEAD_TILT, tilt);
}