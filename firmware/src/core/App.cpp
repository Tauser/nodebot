#include "App.h"
#include <Arduino.h>

// Implementação do método init
void App::init() {
    Serial.println("[APP] Inicializando Sistema...");

    // 1. Inicializar Sistema Nervoso
    Bus.init();

    // 2. Inicializar Serviços de Hardware (Ordem Crítica)
    // _storage.init(); // Ativa o SD Card para carregar texturas
    // _power.init();   // Ativa monitorização de bateria
    _leds.init();    // Ativa os LEDs de feedback (Pino 2)
    
    // Sentidos e Atuadores
    _face.init();    // Inicializa o driver do Display
    // _touch.init();   // Ativa o sensor de toque (Pino 14)
    // _audio.init();   // Ativa o áudio I2S
    // _vision.init();  // Ativa a câmara OV2640

    // 3. Inicializar Cérebro
    //_brain.init(&_face, &_motion); 
    _brain.init(&_face, nullptr); 

    // 4. Criar Tarefas do FreeRTOS
    // Core 1: Focado apenas em Gráficos (60 FPS estáveis)
    xTaskCreatePinnedToCore(
        faceTaskWrapper,
        "FaceLoop",
        8192, 
        this,
        2,
        NULL,
        1 
    );

    // Core 0: Cognição, Sensores e IA
    xTaskCreatePinnedToCore(
        brainTaskWrapper,
        "BrainLoop",
        8192,
        this,
        1,
        NULL,
        0 
    );

    Serial.println("[APP] Sistema Inicializado e Tarefas Criadas.");
}

// Wrappers estáticos para o FreeRTOS
void App::faceTaskWrapper(void* param) {
    static_cast<App*>(param)->runFaceLoop();
}

void App::brainTaskWrapper(void* param) {
    static_cast<App*>(param)->runBrainLoop();
}

// Loop de Expressão (Core 1)
void App::runFaceLoop() {
    uint32_t lastTime = millis();
    
    for(;;) {
        uint32_t now = millis();
        uint32_t deltaTime = now - lastTime;
        lastTime = now;

        // ATENÇÃO: Se isto estiver comentado, a tela fica BRANCA!
        _face.update(deltaTime); 
        
        vTaskDelay(pdMS_TO_TICKS(16)); // ~60Hz
    }
}

// Loop de Inteligência (Core 0)
void App::runBrainLoop() {
    for(;;) {
        // Atualiza sensores em segundo plano
        // _vision.update();
        // _audio.update();
        // _power.update();
        _leds.update();
        
        // Cérebro processa a lógica
        _brain.tick(); 

        // Monitoriza gestos de toque
        // TouchGesture gesture = _touch.detectGesture();
        // if (gesture != TouchGesture::NONE) {
        //     if (gesture == TouchGesture::TAP) Bus.publish(SystemEvent::TOUCH_TAP);
        //     if (gesture == TouchGesture::PETTING) Bus.publish(SystemEvent::TOUCH_PETTING);
        // }
        
        vTaskDelay(pdMS_TO_TICKS(50)); // 20Hz
    }
}