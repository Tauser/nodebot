#include "StorageDriver.h"
#include <Arduino.h>
#include "SD_MMC.h"

bool StorageDriver::init(int clkPin, int cmdPin, int d0Pin) {
    // Configura os pinos exatos que você definiu no mapa de hardware
    SD_MMC.setPins(clkPin, cmdPin, d0Pin);
    
    // Tenta montar o cartão no modo 1-bit (true)
    if (!SD_MMC.begin("/sdcard", true)) {
        return false;
    }
    
    return true;
}