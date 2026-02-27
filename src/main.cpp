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
#include "Actions.h"
#include "WifiSys.h"
#include "SDSys.h"

// Handles das Tarefas (FreeRTOS)
TaskHandle_t TaskHardwareHandle = NULL;
TaskHandle_t TaskTelemetryHandle = NULL;
TaskHandle_t TaskBrainHandle = NULL;

// Estado Global
SystemState currentState = STATE_BOOTING;
EventGroupHandle_t systemEvents;

void TaskHardware(void *pvParameters);
void TaskTelemetry(void *pvParameters);
void TaskBrain(void *pvParameters);

void setup() {
    Serial.begin(115200);
    delay(2000); 
    Serial.println("\n[NODEBOT OS] Iniciando Boot de Nível Industrial...");

    esp_task_wdt_init(5, true); 
    systemEvents = xEventGroupCreate();

    if (!LittleFS.begin(true)) {
        Serial.println("[FATAL] Erro ao montar LittleFS!");
        while(true); 
    }

    bool hwOk = true;
    hwOk &= Lights::iniciar();
    hwOk &= Power::iniciar();
    hwOk &= Display::iniciar();
    hwOk &= Motion::iniciar();
    // hwOk &= AudioSys::iniciar();
    hwOk &= TouchSys::iniciar();
    hwOk &= ImuSys::iniciar();
    // hwOk &= CameraSys::iniciar();
    // hwOk &= SDSys::iniciar();
    
    WifiSys::iniciar();

    if (hwOk) {
        Serial.println("[SYSTEM] Hardware validado. Iniciando RTOS...");
        currentState = STATE_IDLE;
        Display::definirEmocao(EMOCAO_NEUTRO);

        // Core 1: Atuadores - Alta Prioridade
        xTaskCreatePinnedToCore(TaskHardware, "Hardware", 8192, NULL, 3, &TaskHardwareHandle, 1);
        
        // Core 0: Sensores e Conectividade - Prioridade Média/Baixa
        xTaskCreatePinnedToCore(TaskTelemetry, "Telemetry", 4096, NULL, 2, &TaskTelemetryHandle, 0);
        xTaskCreatePinnedToCore(TaskBrain, "Brain", 16384, NULL, 1, &TaskBrainHandle, 0);

        esp_task_wdt_add(TaskHardwareHandle);
        esp_task_wdt_add(TaskTelemetryHandle);
    } else {
        currentState = STATE_CRITICAL_STOP;
        Lights::atualizar(currentState);
    }
}

// ---------------------------------------------------------
// CORE 1: CICLO REAL-TIME (50Hz)
// ---------------------------------------------------------
void TaskHardware(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(20); 

    for (;;) {
        esp_task_wdt_reset(); 
        
        Display::atualizar(currentState);
        Motion::atualizar(currentState);
        AudioSys::atualizar(); 

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// ---------------------------------------------------------
// CORE 0: TELEMETRIA E REFLEXOS (20Hz)
// ---------------------------------------------------------
void TaskTelemetry(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(50);

    for (;;) {
        esp_task_wdt_reset();
        
        Lights::atualizar(currentState);
        Power::monitorar();
        ImuSys::atualizar(); 

        if (currentState != STATE_CRITICAL_STOP && currentState != STATE_SLEEPING) {
            // REFLEXO 1: Queda ou Tombamento
            if (ImuSys::isCaido()) {
                Serial.println("[REFLEXO] Queda detetada!");
                Motion::relaxar(); // Protege os servos
                Display::definirEmocao(EMOCAO_CANSADO);
            } 
            // REFLEXO 2: Carinho (Touch Capacitivo)
            else if (TouchSys::lerTato()) {
                Serial.println("[REFLEXO] Carinho detetado pela fita de cobre!");
                Actions::reagirACarinho(); // <-- Ação completa (Olhos + Som + Motores)
            }
            // REFLEXO 3: Abanão (Susto)
            else if (ImuSys::isAgitado()) {
                Serial.println("[REFLEXO] Abanao detetado!");
                Actions::reagirASusto(); // <-- Ação completa (Olhos + Som + Motores)
            }
        }

        // Monitorização de Bateria Crítica
        if (xEventGroupGetBits(systemEvents) & EVT_BATTERY_LOW) {
            currentState = STATE_CRITICAL_STOP;
        }

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// ---------------------------------------------------------
// CORE 0: INTELIGÊNCIA E COMUNICAÇÃO (10Hz)
// ---------------------------------------------------------
void TaskBrain(void *pvParameters) {
    for (;;) {    
        // A TaskBrain fica dedicada exclusivamente ao Wi-Fi e Servidor Web
        WifiSys::atualizar();
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void loop() { vTaskDelete(NULL); }