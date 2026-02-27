#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

// =========================================================
// 1. MAPEAMENTO DE HARDWARE
// =========================================================
#define SERVO_RX 18
#define SERVO_TX 17
#define LED_PIN  48
#define NUM_LEDS 1
#define ADC_PIN  4

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