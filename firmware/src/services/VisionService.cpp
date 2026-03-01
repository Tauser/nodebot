#include "VisionService.h"
#include "core/config/hardware_config.h"
#include <stdlib.h>
#include <Arduino.h>

void VisionService::init()
{
    _camera.init(
        Hardware::Camera::PIN_XCLK,
        Hardware::Camera::PIN_PCLK,
        Hardware::Camera::PIN_VSYNC,
        Hardware::Camera::PIN_HREF,
        nullptr, // Array de pinos D0-D7 seria passado aqui
        Hardware::Sensors::PIN_I2C_SDA,
        Hardware::Sensors::PIN_I2C_SCL
    );
    _lastBrightness = 0;
    _lastUpdateMs = 0;
}

void VisionService::update()
{
    uint32_t now = millis();
    
    // O processamento de imagem é pesado. Só processamos a cada 250ms (4 FPS)
    if (now - _lastUpdateMs < 250) return;
    _lastUpdateMs = now;

    // Aproveitamos a SUA função original para ler a luz!
    uint8_t currentBrightness = getEnvironmentBrightness();
    uint8_t diferencaLuz = abs(currentBrightness - _lastBrightness);
    _lastBrightness = currentBrightness;

    EventType intencaoDetectada;
    
    // A IA avalia se a sombra rápida na imagem foi de propósito
    if (_classifier.classifyVision(diferencaLuz, intencaoDetectada)) {
        
        if (intencaoDetectada == EventType::INTERACTION_POSITIVE) {
            // Alguém passou a mão perto da câmara para brincar!
            Bus.publish(SystemEvent::TOUCH_TAP); 
        }
    }
}

uint8_t VisionService::getEnvironmentBrightness()
{
    FrameBuffer* fb = _camera.captureFrame();
    if (!fb) return 128; // Retorna um valor médio se falhar

    // Lógica super simples: amostragem rápida pulando bytes para calcular a média de luz
    uint32_t sum = 0;
    uint32_t samples = 0;
    
    // (Se for JPEG, isso é mais complexo, mas assumindo RGB565 ou Grayscale para análise rápida)
    for (size_t i = 0; i < fb->length; i += 64) { 
        sum += fb->data[i];
        samples++;
    }
    
    uint8_t avgBrightness = sum / samples;
    _camera.releaseFrame(fb);
    
    return avgBrightness;
}

bool VisionService::detectSimpleMotion()
{
    uint8_t currentBrightness = getEnvironmentBrightness();
    // Se a luz mudar drasticamente (sombra repentina), assume movimento na frente
    bool motionDetected = (abs(currentBrightness - _lastBrightness) > 40);
    _lastBrightness = currentBrightness;
    return motionDetected;
}

FrameBuffer* VisionService::getFrameForAI()
{
    return _camera.captureFrame();
}

void VisionService::releaseFrame(FrameBuffer* fb)
{
    _camera.releaseFrame(fb);
}