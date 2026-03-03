#pragma once

#include <stdint.h>
#include "../ai/LocalClassifier.h"

enum class SoundType {
    BEEP_SUCCESS,
    BEEP_ERROR,
    WAKE_WORD_DETECTED
};

class AudioService {
public:
    void init();
    void update();
    float getVolume() const;

private:
    LocalClassifier _classifier;
    float _currentVolume = 0.0f;
};