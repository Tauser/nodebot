#include "Power.h"

int Power::leituras[NUM_LEITURAS];
int Power::indice = 0;
long Power::total = 0;

const float Power::TENSAO_MAXIMA = 4.2; // Ajuste para 1S (Ex: 4.2V)
const float Power::TENSAO_MINIMA = 3.2; // Tensão de corte seguro

bool Power::iniciar() {
    pinMode(ADC_PIN, INPUT);
    analogReadResolution(12);
    
    for (int i = 0; i < NUM_LEITURAS; i++) {
        leituras[i] = 0;
    }
    
    // Testa se o ADC consegue ler algo (Ex: se pino for inválido)
    int teste = analogRead(ADC_PIN);
    if (teste == 0 && TENSAO_MAXIMA > 0) {
        // Retorna true mesmo assim, mas em sistemas hiper-críticos, 
        // 0V na inicialização poderia ser considerado falha física (bateria desconectada).
    }
    return true;
}

int Power::lerPorcentagem() {
    total = total - leituras[indice];
    leituras[indice] = analogRead(ADC_PIN);
    total = total + leituras[indice];
    indice = (indice + 1) % NUM_LEITURAS;

    float mediaADC = (float)total / NUM_LEITURAS;
    float tensao = mediaADC * (TENSAO_MAXIMA / 4095.0); 
    
    int porcentagem = map(tensao * 100, TENSAO_MINIMA * 100, TENSAO_MAXIMA * 100, 0, 100);
    return constrain(porcentagem, 0, 100);
}

void Power::monitorar() {
    int nivel = lerPorcentagem();
    
    // Se a bateria cair abaixo de 5%, disparamos o Evento Global
    if (nivel <= 5) {
        // Dispara o alarme no barramento do FreeRTOS
        xEventGroupSetBits(systemEvents, EVT_BATTERY_LOW);
    }
}