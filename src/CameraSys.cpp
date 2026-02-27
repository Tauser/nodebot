#include "CameraSys.h"
#include "SDSys.h"
#include "Config.h" 
#include <SD_MMC.h>

bool CameraSys::iniciar() {
    Serial.println("[SYSTEM] A configurar o Modulo de Camera Freenove...");

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    
    // Usando as variáveis do Config.h
    config.pin_d0 = CAM_Y2_PIN;
    config.pin_d1 = CAM_Y3_PIN;
    config.pin_d2 = CAM_Y4_PIN;
    config.pin_d3 = CAM_Y5_PIN;
    config.pin_d4 = CAM_Y6_PIN;
    config.pin_d5 = CAM_Y7_PIN;
    config.pin_d6 = CAM_Y8_PIN;
    config.pin_d7 = CAM_Y9_PIN;
    config.pin_xclk = CAM_XCLK_PIN;
    config.pin_pclk = CAM_PCLK_PIN;
    config.pin_vsync = CAM_VSYNC_PIN;
    config.pin_href = CAM_HREF_PIN;
    config.pin_sccb_sda = I2C_SDA_PIN;
    config.pin_sccb_scl = I2C_SCL_PIN;
    config.pin_pwdn = -1;
    config.pin_reset = -1;
    
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG; 

    if (psramFound()) {
        config.frame_size = FRAMESIZE_UXGA; 
        config.jpeg_quality = 10;           
        config.fb_count = 2;                
    } else {
        config.frame_size = FRAMESIZE_SVGA; 
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("[ERRO] CameraSys: Falha na inicializacao. Codigo: 0x%x\n", err);
        SDSys::gravarLog("ERRO HARDWARE: Falha ao inicializar a Camera.");
        return false;
    }

    Serial.println("[OK] CameraSys: Olhos fisicos online e focados.");
    return true;
}

void CameraSys::tirarFotoSalvarSD(const char* caminhoFicheiro) {
    Serial.println("[CAMERA] A capturar imagem para o SD...");
    
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("[ERRO] CameraSys: Falha ao capturar a imagem.");
        SDSys::gravarLog("ERRO CAMERA: Falha no Frame Buffer.");
        return;
    }

    File file = SD_MMC.open(caminhoFicheiro, FILE_WRITE);
    if (!file) {
        Serial.println("[ERRO] CameraSys: Falha ao abrir ficheiro no SD_MMC.");
        SDSys::gravarLog("ERRO CAMERA: Nao foi possivel escrever a foto.");
    } else {
        file.write(fb->buf, fb->len);
        file.close();
        Serial.printf("[OK] CameraSys: Fotografia guardada: %s\n", caminhoFicheiro);
    }
    esp_camera_fb_return(fb);
}