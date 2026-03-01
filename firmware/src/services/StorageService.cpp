#include "StorageService.h"
#include "core/config/hardware_config.h"
#include <Arduino.h>

void StorageService::init() {
    _isMounted = _driver.init(
        Hardware::SDCard::PIN_CLK, 
        Hardware::SDCard::PIN_CMD, 
        Hardware::SDCard::PIN_D0
    );

    if (_isMounted) {
        Serial.println("StorageService: SD Card Pronto e Montado.");
    } else {
        Serial.println("StorageService: ERRO - Falha ao montar SD Card!");
    }
}

bool StorageService::isReady() const {
    return _isMounted;
}