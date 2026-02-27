#include <Arduino.h>
#include <LittleFS.h>
#include <esp_task_wdt.h>
#include "Config.h"
#include "Display.h"
#include "Motion.h"
#include "Power.h"
#include "Lights.h"
#include "AudioSys.h"
#include "Touch.h"
#include "Imu.h"
#include "CameraSys.h"
#include "WifiSys.h"
#include "Actions.h"

// Handles das Tarefas do FreeRTOS
TaskHandle_t TaskHardwareHandle = NULL;
TaskHandle_t TaskTelemetryHandle = NULL;
TaskHandle_t TaskBrainHandle = NULL;

SystemState currentState = STATE_BOOTING;
EventGroupHandle_t systemEvents;

void TaskHardware(void *pvParameters);
void TaskTelemetry(void *pvParameters);
void TaskBrain(void *pvParameters);

void setup() {
    Serial.begin(115200);
    delay(2000); 
    Serial.println("\n[NODEBOT OS] Iniciando Sequência de Boot de Nível Industrial...");

    esp_task_wdt_init(5, true); // Watchdog de 5 segundos
    systemEvents = xEventGroupCreate();

    if (!LittleFS.begin(true)) {
        Serial.println("[FATAL] Falha no Disco Rígido (LittleFS)!");
        while(true); // Trava e deixa o Watchdog reiniciar
    }

    // ---------------------------------------------------------
    // BOOT FAIL-FAST: Os 8 Pilares do Hardware
    // ---------------------------------------------------------
    bool hwOk = true;
    hwOk &= Lights::iniciar();
    hwOk &= Power::iniciar();
    hwOk &= Display::iniciar();
    hwOk &= Motion::iniciar();
    hwOk &= AudioSys::iniciar();
    hwOk &= TouchSys::iniciar();
    hwOk &= ImuSys::iniciar();
    hwOk &= CameraSys::iniciar();
    hwOk &= WifiSys::iniciar();

    if (hwOk) {
        Serial.println("[SYSTEM] Todos os sistemas operacionais. Acordando o robô...");
        currentState = STATE_IDLE;
        Display::definirEmocao(EMOCAO_NEUTRO);

        // Core 1 (Motores e Ecrã)
        xTaskCreatePinnedToCore(TaskHardware, "Hardware", 8192, NULL, 3, &TaskHardwareHandle, 1);
        
        // Core 0 (Sensores, Telemetria e Inteligência)
        xTaskCreatePinnedToCore(TaskTelemetry, "Telemetry", 4096, NULL, 2, &TaskTelemetryHandle, 0);
        xTaskCreatePinnedToCore(TaskBrain, "Brain", 16384, NULL, 1, &TaskBrainHandle, 0);

        esp_task_wdt_add(TaskHardwareHandle);
        esp_task_wdt_add(TaskTelemetryHandle);
    } else {
        Serial.println("[CRITICAL] Falha catastrófica de hardware. Modo de Segurança Ativado.");
        currentState = STATE_CRITICAL_STOP;
        Lights::atualizar(currentState);
        Display::atualizar(currentState); 
    }
}

// ---------------------------------------------------------
// CORE 1: ATUADORES (Garante que os movimentos são fluidos)
// ---------------------------------------------------------
void TaskHardware(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(20); // 50 FPS

    for (;;) {
        esp_task_wdt_reset(); 
        Display::atualizar(currentState);
        Motion::atualizar(currentState);
        AudioSys::atualizar(); // Mantém o som a fluir

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// ---------------------------------------------------------
// CORE 0: REFLEXOS (Proteção e Sentidos Rápidos)
// ---------------------------------------------------------
void TaskTelemetry(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(50); // 20 Hz

    for (;;) {
        esp_task_wdt_reset();
        Lights::atualizar(currentState);
        Power::monitorar();
        ImuSys::atualizar(); // Lê o Giroscópio

        if (currentState != STATE_CRITICAL_STOP) {
            // 1. REFLEXO DE QUEDA (Autopreservação)
            if (ImuSys::isCaido()) {
                Serial.println("[ALERTA] Robô caiu! Cortando torque dos motores.");
                Motion::relaxar();
                Display::definirEmocao(EMOCAO_CANSADO); // Ou criar EMOCAO_DOR
            }
            // 2. REFLEXO DE TATO (Carinho)
            else if (TouchSys::lerTato()) {
                Display::definirEmocao(EMOCAO_FELIZ);
            }
            // 3. REFLEXO DE SUSTO (Abanão)
            else if (ImuSys::isAgitado()) {
                Display::definirEmocao(EMOCAO_ZANGADO);
            }
            // Volta ao normal
            else {
                Display::definirEmocao(EMOCAO_NEUTRO);
            }
        }

        if (xEventGroupGetBits(systemEvents) & EVT_BATTERY_LOW) {
            currentState = STATE_CRITICAL_STOP;
        }

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// ---------------------------------------------------------
// CORE 0: CÉREBRO (IA, Visão e Wi-Fi)
// ---------------------------------------------------------
void TaskBrain(void *pvParameters) {
    for (;;) {
        // 1. Processa pedidos Web (Comandos do PC/Telemóvel)
        WifiSys::atualizar();

        // 2. No futuro, aqui entrará o CameraSys::capturarFrame() 
        // para fazer o stream de vídeo via Wi-Fi!

        vTaskDelay(pdMS_TO_TICKS(10)); // 100Hz para resposta rápida
    }
}

void loop() { vTaskDelete(NULL); }