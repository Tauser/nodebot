#include "Power.h"
#include "Config.h"
#include "SDSys.h"

// Voltagem crítica para proteger baterias de Lítio (LiPo/Li-ion)
const float Power::VOLTAGEM_MINIMA = 3.3f;

bool Power::iniciar() {
    pinMode(ADC_PIN, INPUT);
    analogReadResolution(12); // Resolução máxima do ESP32 (0 a 4095)
    
    Serial.println("[SYSTEM] Modulo Power online. Protecao de Bateria ativa.");
    return true;
}

float Power::lerVoltagem() {
    int leituraRaw = analogRead(ADC_PIN);
    
    // Fórmula genérica de conversão para um divisor de tensão 50% (ajustaremos na prática depois se precisar)
    float voltagemReal = (leituraRaw / 4095.0) * 3.3 * 2.0; 
    return voltagemReal;
}

void Power::monitorar() {
    float voltagem = lerVoltagem();
    
    // Ignoramos voltagens abaixo de 1.0V (significa que o robô está ligado por USB e sem bateria inserida)
    if (voltagem < VOLTAGEM_MINIMA && voltagem > 1.0f) { 
        Serial.printf("[AVISO FATAL] Bateria a morrer! (%.2fV)\n", voltagem);
        
        SDSys::gravarLog("BATERIA CRITICA: A entrar em coma para proteger o sistema.");
        
        // Grita para o Cérebro (FreeRTOS) cortar as pernas ao robô imediatamente
        xEventGroupSetBits(systemEvents, EVT_BATTERY_LOW);
    }
}