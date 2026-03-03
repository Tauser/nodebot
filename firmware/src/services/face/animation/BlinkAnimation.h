#pragma once
#include "Animation.h"
#include <Arduino.h>

class BlinkAnimation : public Animation {
private:
    enum class State { IDLE, CLOSING, OPENING };
    State state = State { State::IDLE };
    float nextBlinkTimer = 0;
    float nextBlinkDelay = 3.0f;
    float speed = 22.0f; // Velocidade do piscar

public:
    void update(EyeModel& model, float dt) override {
        switch (state) {
            case State::IDLE:
                nextBlinkTimer += dt;
                if (nextBlinkTimer >= nextBlinkDelay) {
                    state = State::CLOSING;
                    nextBlinkTimer = 0;
                    nextBlinkDelay = random(2000, 6000) / 1000.0f;
                }
                break;

            case State::CLOSING:
                model.blinkFactor -= speed * dt;
                if (model.blinkFactor <= 0.0f) {
                    model.blinkFactor = 0.0f;
                    state = State::OPENING;
                }
                break;

            case State::OPENING:
                model.blinkFactor += speed * dt;
                if (model.blinkFactor >= 1.0f) {
                    model.blinkFactor = 1.0f;
                    state = State::IDLE;
                }
                break;
        }
    }

    void forceBlink() { state = State::CLOSING; }
};