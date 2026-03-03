#include "App.h"
#include <Arduino.h>

App::App() 
    : _brain(_personality, _coordinator) 
{
}

void App::init() {
    Serial.begin(115200);
    delay(1000); 
    
    _displayDriver.init();
    _face.begin(_displayDriver); // Usa o PSRAM detectado no boot!
    _audio.init();
    
    _personality.adjustEnergy(1.0f);

    _lastFaceUpdate = millis();
    _lastBrainUpdate = millis();
    
    Serial.println(">>> NodeBot v1: Sistemas Operacionais. <<<");
}

void App::loop() {
    processSerialCommands();
    runFaceLoop();
    runBrainLoop();
    _audio.update();
}

void App::runFaceLoop() {
    uint32_t now = millis();
    // Alvo de 60 FPS: A suavidade do Delta Time garante o visual orgânico
    if (now - _lastFaceUpdate >= 16) { 
        _face.update(); 
        _lastFaceUpdate = now;
    }
}

void App::runBrainLoop() {
    uint32_t now = millis();
    uint32_t delta = now - _lastBrainUpdate;
    
    if (delta >= 50) { 
        _brain.update(delta);
        _lastBrainUpdate = now;
    }
}

void App::processSerialCommands() {
    if (Serial.available() > 0) {
        char key = Serial.read();
        if (key == '\n' || key == '\r') return; 

        switch (toupper(key)) {
            // --- EXPRESSÕES BÁSICAS ---
            case 'N': _face.setExpression(Expression::NEUTRAL); break;
            case 'H': _face.setExpression(Expression::HAPPY); break;
            case 'A': _face.setExpression(Expression::ANGRY); break;
            case 'S': _face.setExpression(Expression::SAD); break;
            case 'P': _face.setExpression(Expression::SURPRISED); break;
            case 'F': _face.setExpression(Expression::FOCUSED); break;
            case 'K': _face.setExpression(Expression::SKEPTIC); break;
            case 'U': _face.setExpression(Expression::UNIMPRESSED); break;
            case 'W': _face.setExpression(Expression::WORRIED); break;
            case 'R': _face.setExpression(Expression::FURIOUS); break;
            case 'Q': _face.setExpression(Expression::SQUINT); break;
            case 'C': _face.setExpression(Expression::SUSPICIOUS); break;

            // --- COMANDOS ESPECIAIS (ADICIONADOS) ---
            case 'X': // Inicia o Modo SCAN (Busca frenética)
                _face.engine.scan.start();
                Serial.println("Modo SCAN: Ativado!");
                break;
            case 'O': // Para o SCAN (OK / STOP)
                _face.engine.scan.stop();
                _face.setExpression(Expression::NEUTRAL);
                Serial.println("Modo SCAN: Parado.");
                break;
            case '!': // Simula um impacto físico (SHOCK)
                _face.onPhysicalImpact(3.5f); // 3.5G de força virtual
                Serial.println("Simulação: IMPACTO detectado!");
                break;

            default: 
                Serial.println("Comando Serial: Letra desconhecida."); 
                return;
        }
        
        Serial.printf("NodeBot: Comando [%c] processado.\\n", key);
    }
}