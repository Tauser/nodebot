#include "App.h"
#include <Arduino.h>

App::App() 
    : _brain(_personality, _coordinator) // Injeção de dependência no cérebro
{
}

void App::init() {
    Serial.begin(115200);
    delay(1000); 
    
    _displayDriver.init();
    _face.begin(_displayDriver);
    _audio.init();
    
    _personality.adjustEnergy(1.0f);

    // CRUCIAL: Inicialize os tempos para o delta não vir "quebrado"
    _lastFaceUpdate = millis();
    _lastBrainUpdate = millis();
    
    Serial.println(">>> FaceService: Pronto! <<<");
}

void App::loop() {
    processSerialCommands();
    runFaceLoop();
    runBrainLoop();
    _audio.update();
}

void App::runFaceLoop() {
    uint32_t now = millis();
    // Alvo de 60 FPS (1000ms / 60 = ~16ms por quadro)
    if (now - _lastFaceUpdate >= 16) { 
        _face.update(); 
        _lastFaceUpdate = now;
    }
}

void App::runBrainLoop() {
    uint32_t now = millis();
    uint32_t delta = now - _lastBrainUpdate;
    
    // 20Hz Loop Cognitivo (pensamento)
    if (delta >= 50) { 
        _brain.update(delta);
        _lastBrainUpdate = now;
    }
}

void App::processSerialCommands() {
    // Se chegou algum caractere no Monitor Serial
    if (Serial.available() > 0) {
        char key = Serial.read();
        
        // Ignora lixo de "Enter" e "Quebra de linha"
        if (key == '\n' || key == '\r') return; 

        // Repassa o comando direto para o serviço de rosto!
        switch (key) {
            case 'N': case 'n': _face.setExpression(Expression::NEUTRAL); break;
            case 'H': case 'h': _face.setExpression(Expression::HAPPY); break;
            case 'A': case 'a': _face.setExpression(Expression::ANGRY); break;
            case 'S': case 's': _face.setExpression(Expression::SAD); break;
            case 'P': case 'p': _face.setExpression(Expression::SURPRISED); break;
            case 'F': case 'f': _face.setExpression(Expression::FOCUSED); break;
            case 'K': case 'k': _face.setExpression(Expression::SKEPTIC); break;
            case 'U': case 'u': _face.setExpression(Expression::UNIMPRESSED); break;
            case 'W': case 'w': _face.setExpression(Expression::WORRIED); break;
            case 'R': case 'r': _face.setExpression(Expression::FURIOUS); break;
            case 'Q': case 'q': _face.setExpression(Expression::SQUINT); break;
            case 'C': case 'c': _face.setExpression(Expression::SUSPICIOUS); break;
            case 'B': case 'b': _face.setExpression(Expression::SURPRISED); break;
            default: 
                Serial.println("Comando Serial: Letra desconhecida."); 
                return;
        }
        
        Serial.print("Comando Serial: Mudando expressao para [");
        Serial.print(key);
        Serial.println("]");
    }
}