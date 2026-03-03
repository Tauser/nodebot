#pragma once
#include "Animation.h"

class EmotionTransition : public Animation {
public:
    float happyW = 0, angryW = 0, sadW = 0, skepticW = 0, focusedW = 0,
          surprisedW = 0, unimpressedW = 0, worriedW = 0, furiousW = 0,
          squintW = 0, suspiciousW = 0;
    float speed = 12.0f;

    void update(EyeModel& model, float dt) override {
        auto cur = model.currentExpression;
        auto lerpW = [&](float &w, bool cond) { w += (cond - w) * (speed * dt); };

        lerpW(happyW, cur == Expression::HAPPY);
        lerpW(angryW, cur == Expression::ANGRY);
        lerpW(sadW, cur == Expression::SAD);
        lerpW(skepticW, cur == Expression::SKEPTIC);
        lerpW(focusedW, cur == Expression::FOCUSED);
        lerpW(surprisedW, cur == Expression::SURPRISED);
        lerpW(unimpressedW, cur == Expression::UNIMPRESSED);
        lerpW(worriedW, cur == Expression::WORRIED);
        lerpW(furiousW, cur == Expression::FURIOUS);
        lerpW(squintW, cur == Expression::SQUINT);
        lerpW(suspiciousW, cur == Expression::SUSPICIOUS);
    }
};