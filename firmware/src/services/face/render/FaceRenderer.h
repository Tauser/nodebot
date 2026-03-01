#pragma once
#include "../model/EyeModel.h"
#include "drivers/DisplayDriver.h" // Ajusta o caminho se o teu driver estiver noutra pasta
#include <Adafruit_GFX.h>

class FaceRenderer {
public:
    void init();
    void render(const EyeModel& eye);

private:
    DisplayDriver _display;
    
    // Buffer de memória para Double Buffering (Adeus pisca-pisca!)
    GFXcanvas16* _canvas = nullptr;
    
    // Estado interno para suavização (Physics State)
    EyeState _current; 
};