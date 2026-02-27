#include "CameraSys.h"

camera_config_t CameraSys::configCamera;

bool CameraSys::iniciar() {
    // Pinos padrão para módulos de câmara no ESP32-S3
    // (Ajuste no Config.h de acordo com a sua placa específica, ex: Freenove, ESP32-S3-EYE, etc.)
    configCamera.pin_pwdn = -1;
    configCamera.pin_reset = -1;
    configCamera.pin_xclk = 15;
    configCamera.pin_sscb_sda = 4;
    configCamera.pin_sscb_scl = 5;
    configCamera.pin_d7 = 16;
    configCamera.pin_d6 = 17;
    configCamera.pin_d5 = 18;
    configCamera.pin_d4 = 12;
    configCamera.pin_d3 = 10;
    configCamera.pin_d2 = 8;
    configCamera.pin_d1 = 9;
    configCamera.pin_d0 = 11;
    configCamera.pin_vsync = 6;
    configCamera.pin_href = 7;
    configCamera.pin_pclk = 13;

    // Configuração de Memória e Qualidade
    configCamera.ledc_channel = LEDC_CHANNEL_0;
    configCamera.ledc_timer = LEDC_TIMER_0;
    configCamera.xclk_freq_hz = 20000000;
    configCamera.pixel_format = PIXFORMAT_JPEG; // JPEG direto do hardware!
    
    // Se temos a PSRAM OPI que você comprou, usamos alta performance
    if (psramFound()) {
        configCamera.frame_size = FRAMESIZE_QVGA; // 320x240 (Ideal para CV/Streaming)
        configCamera.jpeg_quality = 12;           // Qualidade alta (0-63, menor é melhor)
        configCamera.fb_count = 2;                // Usa 2 buffers para não perder frames
        configCamera.grab_mode = CAMERA_GRAB_LATEST; // Pega sempre a imagem mais recente
    } else {
        Serial.println("[FATAL] CameraSys: PSRAM não encontrada! A câmara precisa de PSRAM.");
        return false;
    }

    // Inicializa o Hardware
    esp_err_t err = esp_camera_init(&configCamera);
    if (err != ESP_OK) {
        Serial.printf("[ERRO] CameraSys: Falha ao iniciar a câmara (Erro: 0x%x)\n", err);
        return false;
    }

    // Ajustes de imagem orgânica (evitar superexposição)
    sensor_t * sensor = esp_camera_sensor_get();
    sensor->set_vflip(sensor, 1);   // Inverte se a câmara estiver de cabeça para baixo
    sensor->set_hmirror(sensor, 1); // Espelha a imagem
    
    Serial.println("[OK] CameraSys: Módulo de Visão online e gravando em PSRAM.");
    return true;
}

camera_fb_t* CameraSys::capturarFrame() {
    return esp_camera_fb_get(); // Tira a foto
}

void CameraSys::liberarFrame(camera_fb_t* fb) {
    if (fb) {
        esp_camera_fb_return(fb); // Limpa a memória
    }
}