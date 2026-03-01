#include <Arduino.h>
#include "EmotionModel.h"

Emotion EmotionModel::predict(float energy, float stimulation, float curiosity, float sociabilityBias) {
    // 1. Sobrevivência primeiro
    if (energy < 0.15f) return Emotion::SLEEPING;

    // 2. Cálculo do limiar de felicidade (influenciado pela sociabilidade aprendida)
    float happyThreshold = 0.5f - (sociabilityBias * 0.5f); // Robô sociável precisa de menos estímulo para ficar feliz

    // 3. Matriz de Inferência Heurística (Espaço Latente Offline)
    if (stimulation > 0.8f && energy > 0.5f) {
        return Emotion::SURPRISED; // Muito estímulo repentino
    }
    
    if (stimulation > happyThreshold && curiosity > 0.4f) {
        return Emotion::HAPPY; // Estímulo positivo e interessado
    }
    
    if (curiosity < 0.2f && energy > 0.3f) {
        return Emotion::SAD; // Entediado (pouca curiosidade) mas acordado
    }
    
    if (stimulation > 0.6f && curiosity < 0.3f) {
        return Emotion::ANGRY; // Muito barulho/estímulo, mas ele não está interessado (irritado)
    }

    return Emotion::NEUTRAL; // Estado base
}