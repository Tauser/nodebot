#include "Actions.h"
#include "Motion.h"
#include "Display.h"
#include "AudioSys.h"

void Actions::dizerSim() {
    for(int i=0; i<2; i++) {
        Motion::olharPara(2048, 2400, 1500, 100); // Baixo
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2048, 1700, 1500, 100); // Cima
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::dizerNao() {
    for(int i=0; i<2; i++) {
        Motion::olharPara(1600, 2048, 1500, 100); // Esquerda
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2500, 2048, 1500, 100); // Direita
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::olharCurioso() {
    Motion::olharPara(2300, 1800, 400, 20); // Movimento lento e inclinado
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::reagirACarinho() {
    Display::definirEmocao(EMOCAO_FELIZ);
    Motion::olharPara(2048, 1800, 500, 50); // Levanta um pouco a cabeça
    vTaskDelay(pdMS_TO_TICKS(800));
    centralizarSuave();
}

void Actions::reagirASusto() {
    Display::definirEmocao(EMOCAO_ZANGADO);
    Motion::olharPara(2048, 2600, 2000, 250); // Recuo rápido para baixo
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::centralizarSuave() {
    Motion::olharPara(2048, 2048, 500, 30);
}