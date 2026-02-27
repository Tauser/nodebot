#include "SDSys.h"

bool SDSys::iniciar() {
    Serial.println("[SYSTEM] Montando Cartao SD...");
    
    // Inicia o barramento SPI padrão do ESP32 para o SD
    if (!SD.begin(PINO_CS)) {
        Serial.println("[ERRO] SDSys: Falha ao montar o Cartao SD! Verifique os pinos.");
        return false;
    }
    
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("[ERRO] SDSys: Nenhum cartao SD inserido.");
        return false;
    }

    Serial.println("[OK] SDSys: Cartao SD montado com sucesso.");
    gravarLog("--- NODEBOT OS INICIADO ---");
    
    return true;
}

void SDSys::gravarLog(const char* evento) {
    // FILE_APPEND adiciona texto ao final do ficheiro sem apagar o passado
    File file = SD.open("/nodebot_log.txt", FILE_APPEND);
    if (file) {
        file.printf("[%lu ms] %s\n", millis(), evento);
        file.close();
    } else {
        Serial.println("[ERRO] SDSys: Nao foi possivel escrever no SD.");
    }
}