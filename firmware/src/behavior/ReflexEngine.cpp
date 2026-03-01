#include "ReflexEngine.h"

void ReflexEngine::init(FaceService* face, MotionService* motion) {
    _face = face;
    _motion = motion;
}

void ReflexEngine::onLoudNoise() {
    // Reflexo de sobressalto: Pisca os olhos e encolhe a cabeça instantaneamente
    if (_face) _face->triggerBlink();
    if (_motion) {
        // Assume uma postura defensiva (ex: pescoço para baixo rápido)
        _motion->lookDown();
    }
}

void ReflexEngine::onSuddenDrop() {
    // O IMU detetou queda livre!
    if (_face) _face->showEmotion(Emotion::SURPRISED); // Olhos arregalados de pânico
    if (_motion) {
        // Centraliza os motores para tentar proteger os eixos de danos na pancada
        _motion->lookCenter();
    }
}