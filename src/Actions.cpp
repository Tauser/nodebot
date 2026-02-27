#include "Actions.h"
#include "Motion.h"
#include "Display.h"
#include "AudioSys.h"

void Actions::dizerSim() {
    // Intenção: Foca o olhar antes de mover
    Display::definirEmocao(EMOCAO_NEUTRO);
    vTaskDelay(pdMS_TO_TICKS(100)); // Atraso cognitivo natural
    
    for(int i=0; i<2; i++) {
        Motion::olharPara(2048, 2400, 1500, 100); // Baixo
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2048, 1700, 1500, 100); // Cima
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::dizerNao() {
    // Intenção: Foca o olhar
    Display::definirEmocao(EMOCAO_NEUTRO);
    vTaskDelay(pdMS_TO_TICKS(100));
    
    for(int i=0; i<2; i++) {
        Motion::olharPara(1600, 2048, 1500, 100); // Esquerda
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2500, 2048, 1500, 100); // Direita
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::olharCurioso() {
    // Intenção: Foca no estímulo
    Display::definirEmocao(EMOCAO_NEUTRO);
    vTaskDelay(pdMS_TO_TICKS(150)); 
    
    // Ação: Movimento lento e inclinado
    Motion::olharPara(2300, 1800, 400, 20); 
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::reagirACarinho() {
    // Intenção imediata: Fica feliz no exato milissegundo do toque!
    Display::definirEmocao(EMOCAO_FELIZ);
    vTaskDelay(pdMS_TO_TICKS(150)); // Saboreia o momento
    
    // Ação: Levanta um pouco a cabeça e relaxa
    Motion::olharPara(2048, 1800, 500, 50); 
    vTaskDelay(pdMS_TO_TICKS(800));
    centralizarSuave();
}

void Actions::reagirASusto() {
    // Intenção imediata: Olhar de fúria/alerta em 0ms
    Display::definirEmocao(EMOCAO_ZANGADO);
    vTaskDelay(pdMS_TO_TICKS(100)); // O corpo reage logo a seguir
    
    // Ação: Recuo rápido para baixo para se proteger
    Motion::olharPara(2048, 2600, 2000, 250); 
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::centralizarSuave() {
    // Volta ao estado neutro
    Display::definirEmocao(EMOCAO_NEUTRO);
    Motion::olharPara(2048, 2048, 500, 30);
    // Não precisa de delay aqui pois é uma função de finalização
}