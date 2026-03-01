#pragma once
#include <stdint.h>

class StorageDriver {
public:
    bool init(int clkPin, int cmdPin, int d0Pin);
    
    // Na Fase 6, adicionaremos aqui métodos como readFile(), writeFile(), etc.
};