#include "Actions.h"
#include "Motion.h"
#include "Display.h"
#include "AudioSys.h"

void Actions::dizerSim() {
    Display::definirEmocao(EMOCAO_NEUTRO);
    AudioSys::tocar("/sim.mp3"); // <--- O SOM DISPARA AQUI!
    vTaskDelay(pdMS_TO_TICKS(100)); // Atraso cognitivo natural
    
    for(int i=0; i<2; i++) {
        Motion::olharPara(2048, 2400, 1500, 100); 
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2048, 1700, 1500, 100); 
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::dizerNao() {
    Display::definirEmocao(EMOCAO_NEUTRO);
    AudioSys::tocar("/nao.mp3");
    vTaskDelay(pdMS_TO_TICKS(100));
    
    for(int i=0; i<2; i++) {
        Motion::olharPara(1600, 2048, 1500, 100); 
        vTaskDelay(pdMS_TO_TICKS(250));
        Motion::olharPara(2500, 2048, 1500, 100); 
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    centralizarSuave();
}

void Actions::olharCurioso() {
    Display::definirEmocao(EMOCAO_NEUTRO);
    AudioSys::tocar("/curioso.mp3"); // Um beep interrogativo (tom a subir)
    vTaskDelay(pdMS_TO_TICKS(150)); 
    
    Motion::olharPara(2300, 1800, 400, 20); 
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::reagirACarinho() {
    Display::definirEmocao(EMOCAO_FELIZ);
    AudioSys::tocar("/feliz.mp3"); // Um som suave, como um ronronar robótico
    vTaskDelay(pdMS_TO_TICKS(150)); 
    
    Motion::olharPara(2048, 1800, 500, 50); 
    vTaskDelay(pdMS_TO_TICKS(800));
    centralizarSuave();
}

void Actions::reagirASusto() {
    Display::definirEmocao(EMOCAO_ZANGADO);
    AudioSys::tocar("/susto.mp3"); // Um beep agudo e de alerta
    vTaskDelay(pdMS_TO_TICKS(100)); 
    
    Motion::olharPara(2048, 2600, 2000, 250); 
    vTaskDelay(pdMS_TO_TICKS(1000));
    centralizarSuave();
}

void Actions::centralizarSuave() {
    Display::definirEmocao(EMOCAO_NEUTRO);
    Motion::olharPara(2048, 2048, 500, 30);
}