#include "FaceService.h"
#include "../../drivers/DisplayDriver.h"

void FaceService::begin(DisplayDriver& driver) {
    _tft = driver.getLGFX();
    
    // Voltamos para 16-bit e PSRAM ligado para caber com folga
    canvas.setColorDepth(16); 
    canvas.setPsram(true);  
    canvas.createSprite(240, 240);
    
    renderer.init(&canvas);
    _lastMillis = millis();
    Serial.println(">>> FaceService: Pronto (16-bit DMA Mode)! <<<");
}

void FaceService::update() {
    float dt = (millis() - _lastMillis) / 1000.0f;
    _lastMillis = millis();
    
    // Aliviando a trava do Wokwi: 
    // Se o simulador engasgar, não deixa a animação entrar em "câmera lenta extrema"
    if (dt <= 0 || dt > 0.3f) dt = 0.033f; 

    if (_isBooting) {
        bootAnim.update(model, dt);
        if (bootAnim.isFinished()) _isBooting = false;
    } else {
        engine.update(model, dt);
    }

    // A otimização matemática continua aqui (limpa só o que precisa)
    renderer.render(model, dt, engine.transition);
    
    // ENVIO PURO VIA DMA: Manda o bloco inteiro de uma vez!
    // Sem ClipRect, o hardware de 80MHz brilha sem a CPU atrapalhar.
    canvas.pushSprite(_tft, 40, 0); 
}

void FaceService::setExpression(Expression exp) {
    model.currentExpression = exp;
    engine.idle.resetActivity();
}

void FaceService::onPhysicalImpact(float gForce) {
    engine.impact.trigger(gForce - 1.0f);
    setExpression(Expression::SURPRISED);
}