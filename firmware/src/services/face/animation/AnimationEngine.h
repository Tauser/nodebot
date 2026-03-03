#pragma once
#include <vector>
#include "Animation.h"
#include "BlinkAnimation.h"
#include "SaccadeAnimation.h"
#include "EmotionTransition.h"
#include "ScanAnimation.h"
#include "ImpactAnimation.h"
#include "IdleBehavior.h"

class AnimationEngine {
public:
    AnimationEngine();
    void update(EyeModel& model, float dt);

    // Instâncias das animações (Públicas para acesso via FaceService)
    BlinkAnimation blink;
    SaccadeAnimation saccade;
    EmotionTransition transition;
    ScanAnimation scan;
    ImpactAnimation impact;
    IdleBehavior idle;

private:
    std::vector<Animation*> animations;
};