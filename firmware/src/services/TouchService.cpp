#include "TouchService.h"
#include "core/config/hardware_config.h"
#include <Arduino.h>

void TouchService::init()
{
    _touchPin = Hardware::Sensors::PIN_TOUCH;
    _threshold = Hardware::Sensors::TOUCH_THRESHOLD;
    _wasTouched = false;
    _touchStartTime = 0;
}

bool TouchService::isBeingTouched()
{
    // Lê o pino capacitivo do ESP32 (ou de um driver I2C se usasse um TTP223)
    uint16_t touchValue = touchRead(_touchPin);
    return (touchValue < _threshold); // No ESP32, o valor cai quando tocado
}

TouchGesture TouchService::detectGesture()
{
    bool currentlyTouched = isBeingTouched();
    TouchGesture result = TouchGesture::NONE;

    if (currentlyTouched && !_wasTouched) {
        // Começou a tocar agora
        _touchStartTime = millis();
        _wasTouched = true;
    } 
    else if (!currentlyTouched && _wasTouched) {
        // Tirou a mão. Vamos calcular o tempo que esteve a tocar!
        uint32_t duration = millis() - _touchStartTime;
        
        if (duration > 50 && duration < 500) {
            result = TouchGesture::TAP; // Toque rápido
        } 
        else if (duration >= 500) {
            result = TouchGesture::PETTING; // Carinho longo
        }
        
        _wasTouched = false;
    }

    return result;
}