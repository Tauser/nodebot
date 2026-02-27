#include "SDSys.h"
#include "Config.h"

bool SDSys::iniciar() {
    Serial.println("[SYSTEM] Montando Cartao SD via SD_MMC (Freenove Nativo)...");
    
    // Configura a pinagem exata do slot SD da Freenove ESP32-S3-WROOM CAM
    SD_MMC.setPins(SD_CLK_PIN, SD_CMD_PIN, SD_D0_PIN);
    
    // Inicia em modo 1-bit (true) para estabilidade máxima e evitar conflitos com a câmara
    if (!SD_MMC.begin("/sdcard", true)) {
        Serial.println("[ERRO] SDSys: Falha ao montar o Cartao SD_MMC!");
        return false;
    }
    
    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("[ERRO] SDSys: Nenhum cartao SD inserido.");
        return false;
    }

    Serial.println("[OK] SDSys: Cartao SD_MMC montado com sucesso (Alta Velocidade).");
    gravarLog("--- NODEBOT OS INICIADO ---");
    
    return true;
}

void SDSys::gravarLog(const char* evento) {
    // Agora usamos o SD_MMC para abrir ficheiros
    File file = SD_MMC.open("/nodebot_log.txt", FILE_APPEND);
    if (file) {
        file.printf("[%lu ms] %s\n", millis(), evento);
        file.close();
    } else {
        Serial.println("[ERRO] SDSys: Nao foi possivel escrever log no SD.");
    }
}