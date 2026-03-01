#pragma once

enum class Emotion {
    NEUTRAL,
    HAPPY,
    SAD,
    ANGRY,
    SURPRISED,
    SLEEPING,
    SUSPICIOUS
};

struct EyeState {
    float pupilX = 0.0f;    // -1.0 (Esquerda) a 1.0 (Direita)
    float pupilY = 0.0f;    // -1.0 (Cima) a 1.0 (Baixo)
    float pupilSize = 1.0f; // Multiplicador de escala (1.0 = normal)
    float lidOpen = 1.0f;   // 1.0 (Aberto) a 0.0 (Fechado)
};

class EyeModel {
private:
    EyeState _state;

public:
    EyeState& get() { return _state; }
    const EyeState& get() const { return _state; }
    
    void setPupil(float x, float y) { 
        _state.pupilX = x; 
        _state.pupilY = y; 
    }
    
    void setPupilSize(float size) { 
        _state.pupilSize = size; 
    }
    
    void setLid(float open) { 
        _state.lidOpen = open; 
    }
};