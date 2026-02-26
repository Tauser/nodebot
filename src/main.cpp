#include <Arduino.h>
#include "Display.h"
#include "Config.h"

// Handles para as tarefas
TaskHandle_t TaskBrainHandle;
TaskHandle_t TaskHardwareHandle;

// Protótipos das funções das tarefas
void TaskBrain(void *pvParameters);
void TaskHardware(void *pvParameters);

void setup() {
    Serial.begin(115200);

    // 1. Inicializar Hardware Crítico (Display)
    Display::iniciar();

    // 2. Criar a Tarefa do Cérebro (Core 0)
    xTaskCreatePinnedToCore(
        TaskBrain,          // Função da tarefa
        "TaskBrain",        // Nome
        8192,               // Stack size (8KB)
        NULL,               // Parâmetros
        1,                  // Prioridade
        &TaskBrainHandle,   // Handle
        0                   // Core 0
    );

    // 3. Criar a Tarefa do Hardware (Core 1)
    xTaskCreatePinnedToCore(
        TaskHardware,
        "TaskHardware",
        8192,
        NULL,
        2,                  // Prioridade maior para o hardware/movimento
        &TaskHardwareHandle,
        1                   // Core 1
    );
}

// Loop do Core 0: Inteligência e Comunicação
void TaskBrain(void *pvParameters) {
    for (;;) {
        // Exemplo: Checar preço do Bitcoin ou processar voz aqui
        // Serial.println("[Core 0] Processando lógica de IA...");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

// Loop do Core 1: Movimento e Visual
void TaskHardware(void *pvParameters) {
    for (;;) {
        // Exemplo: Atualizar animação dos olhos e servos
        Display::piscar();
        vTaskDelay(pdMS_TO_TICKS(3000)); // Pisca a cada 3 segundos
    }
}

void loop() {
    // O loop principal fica vazio ou pode ser usado para monitoramento
    vTaskDelete(NULL); 
}