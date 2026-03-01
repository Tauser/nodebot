#pragma once
#include <stdint.h>
#include "drivers/CameraDriver.h"

// --- NOVO: Integração com a IA e Sistema Nervoso ---
#include "ai/LocalClassifier.h"
#include "core/EventBus.h"

class VisionService
{
public:
    void init();
    void update(); // NOVO: Loop de visão

    // Capacidades Offline Básicas
    uint8_t getEnvironmentBrightness(); 
    bool detectSimpleMotion();          

    // Preparação para quando a IA chegar
    FrameBuffer* getFrameForAI();
    void releaseFrame(FrameBuffer* fb);

private:
    CameraDriver _camera;
    LocalClassifier _classifier; // NOVO: O Cérebro Visual
    uint8_t _lastBrightness; 
    uint32_t _lastUpdateMs;      // NOVO: Controle de tempo para não torrar CPU
};