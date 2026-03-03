#include <Arduino.h>
#include "core/App.h"

// Instância global da aplicação
App nodeBot; 

void setup() {
    Serial.begin(115200);
    
    // A App inicializa tudo e distribui as Tasks pelos núcleos
    nodeBot.init(); 
}

void loop() {
    nodeBot.loop();
    // vTaskDelete(NULL); // REMOVIDO: Isso matava o loop principal!
}