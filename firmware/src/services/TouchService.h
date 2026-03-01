#pragma once
#include <stdint.h>

// Intenções extraídas do Hardware
enum class TouchGesture {
    NONE,
    TAP,       // Toque rápido (ex: chamar atenção)
    PETTING    // Toque longo/suave (ex: carinho)
};

class TouchService
{
public:
    void init();

    // API de Intenção
    bool isBeingTouched();
    TouchGesture detectGesture();

private:
    // (Assumindo que temos um TouchDriver básico ou usando a API do ESP32 isolada aqui)
    int _touchPin;
    int _threshold;
    
    // Estado funcional para debouncing e tempo de toque
    uint32_t _touchStartTime;
    bool _wasTouched;
};