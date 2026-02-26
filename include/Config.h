#pragma once

// ==========================================
// 🤖 NodeBot - Configurações de Hardware
// Placa: Freenove ESP32-S3 (WROOM N16R8)
// ==========================================

// --- 📺 Tela (Display IPS 2" - SPI) ---
// Nota: O ESP32-S3 tem roteamento flexível de pinos (Matrix).
// Estes são excelentes pinos padrão, mas podemos remapear na montagem.
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8
#define TFT_BL   14 // Backlight (Para controlarmos o brilho no futuro)

// --- 🗣️ Áudio (MAX98357A - I2S) ---
#define I2S_BCLK 4  // Bit Clock
#define I2S_LRC  5  // Left/Right Clock (Word Select)
#define I2S_DOUT 6  // Data Out (Vai ligado no pino DIN do módulo)

// --- 🦾 Motores (Feetech SCS0009 - UART/Serial) ---
// Usaremos a Serial1 de hardware do ESP32 para falar com os servos
// sem atrapalhar a porta USB (Serial0)
#define SERVO_RX 18
#define SERVO_TX 17

// --- 🌐 Wi-Fi (Para a IA e integração futura) ---
#define WIFI_SSID "NOME_DA_REDE"
#define WIFI_PASS "SENHA_DA_REDE"