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
    // Apaga a task nativa do Arduino para poupar RAM.
    // O NodeBot agora vive nas Tasks do FreeRTOS criadas pela App!
    vTaskDelete(NULL); 
}