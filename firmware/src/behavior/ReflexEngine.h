#pragma once
#include "services/face/FaceService.h"
#include "services/MotionService.h"

// O ReflexEngine é injetado com os Services diretamente para ter "Bypass" cognitivo
class ReflexEngine {
public:
    void init(FaceService* face, MotionService* motion);
    
    // Chamado por interrupções ou tasks muito rápidas (ex: som alto súbito)
    void onLoudNoise(); 
    void onSuddenDrop(); // IMU detetou queda livre

private:
    FaceService* _face;
    MotionService* _motion;
};