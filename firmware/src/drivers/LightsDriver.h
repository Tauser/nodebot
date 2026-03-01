#pragma once
#include <stdint.h>
#include <FastLED.h>

class LedDriver {
public:
    void init(int pin, int numLeds);
    void setLedColor(int index, uint8_t r, uint8_t g, uint8_t b);
    void show();
    void clear();

private:
    int _numLeds;
    CRGB* _leds;
};