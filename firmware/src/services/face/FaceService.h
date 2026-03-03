#pragma once
#include <LovyanGFX.hpp>
#include "model/EyeModel.h"
#include "render/FaceRenderer.h"
#include "animation/AnimationEngine.h"
#include "animation/BootAnimation.h"

// Forward declaration do seu driver
class DisplayDriver; 

class FaceService {
public:
    void begin(DisplayDriver& driver);
    void update();
    void setExpression(Expression exp);
    void onPhysicalImpact(float gForce);
    
    AnimationEngine engine;

private:
    lgfx::LGFX_Device* _tft;
    lgfx::LGFX_Sprite canvas;
    EyeModel model;
    FaceRenderer renderer;
    BootAnimation bootAnim;
    unsigned long _lastMillis = 0;
    bool _isBooting = true;
};