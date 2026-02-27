#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

// =========================================================
// 1. MAPEAMENTO GLOBAL DE HARDWARE (Freenove ESP32-S3)
// =========================================================

// --- MOTORES (Serial 1) ---
#define SERVO_RX_PIN 3
#define SERVO_TX_PIN 1

// --- ENERGIA E LUZES ---
#define LED_PIN  41  
#define NUM_LEDS 1
#define ADC_PIN  19  

// --- TATO (Touch Capacitivo) ---
#define TOUCH_PIN 14
#define TOUCH_CAPACITIVE_THRESHOLD 30000

// --- ÁUDIO (I2S - MAX98357A) ---
#define I2S_BCLK_PIN 35
#define I2S_LRC_PIN  36
#define I2S_DOUT_PIN 37

// --- I2C PARTILHADO (IMU MPU6050 & Configuração da Câmera) ---
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

// --- SD CARD (SD_MMC Alta Velocidade Interno) ---
#define SD_CMD_PIN 38
#define SD_CLK_PIN 39
#define SD_D0_PIN  40

// --- CÂMERA OV2640 (Uso Interno Freenove) ---
#define CAM_XCLK_PIN  15
#define CAM_Y9_PIN    16
#define CAM_Y8_PIN    17
#define CAM_Y7_PIN    18
#define CAM_Y6_PIN    12
#define CAM_Y5_PIN    10
#define CAM_Y4_PIN    8
#define CAM_Y3_PIN    9
#define CAM_Y2_PIN    11
#define CAM_VSYNC_PIN 6
#define CAM_HREF_PIN  7
#define CAM_PCLK_PIN  13

// --- ECRÃ TFT (SPI) - *APENAS DOCUMENTAÇÃO* ---
// NOTA: A biblioteca TFT_eSPI é a única que não aceita variáveis externas. 
// Estes pinos DEVEM ser configurados diretamente no ficheiro User_Setup.h dela!
// TFT_MOSI 47 | TFT_SCLK 21 | TFT_CS 45 | TFT_DC 48 | TFT_RST 2

// =========================================================
// 2. MÁQUINA DE ESTADOS GLOBAL (FSM)
// =========================================================
enum SystemState {
    STATE_BOOTING,       // Iniciando e testando hardware
    STATE_IDLE,          // Saudável, respirando, esperando
    STATE_INTERACTING,   // Executando comando (voz, IA, etc)
    STATE_SLEEPING,      // <-- ADICIONADO: Poupando bateria / descansando
    STATE_CRITICAL_STOP, // Falha de bateria ou hardware
    STATE_RECOVERY       // Tentando se recuperar de um erro
};

// =========================================================
// 3. EMOÇÕES
// =========================================================
enum Emocao {
    EMOCAO_NEUTRO,
    EMOCAO_FELIZ,
    EMOCAO_ZANGADO,
    EMOCAO_CANSADO
};

// =========================================================
// 4. BARRAMENTO DE EVENTOS 
// =========================================================
#define EVT_HW_DISPLAY_OK   (1 << 0) // Bit 0
#define EVT_HW_MOTION_OK    (1 << 1) // Bit 1
#define EVT_BATTERY_LOW     (1 << 2) // Bit 2
#define EVT_ENTER_SLEEP     (1 << 3) // Bit 3

// =========================================================
// Variáveis Globais
// =========================================================
extern SystemState currentState;
extern EventGroupHandle_t systemEvents;