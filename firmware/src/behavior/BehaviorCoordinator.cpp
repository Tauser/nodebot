#include "BehaviorCoordinator.h"

BehaviorCoordinator::BehaviorCoordinator() {
    _faceDetected = false;
    _faceX = 0.0f;
    _faceY = 0.0f;
    _nextFaceCommand.isValid = false;
}

void BehaviorCoordinator::setFaceDetected(bool detected, float x, float y) {
    _faceDetected = detected;
    _faceX = x;
    _faceY = y;
}

void BehaviorCoordinator::arbitrate(const InternalState& state) {
    _nextFaceCommand.isValid = true;
    _nextFaceCommand.emotion = state.currentEmotion;

    // Regra 1: Se estiver com sono, ignora o mundo e fecha os olhos (metaforicamente)
    if (state.currentEmotion == Emotion::SLEEPY) {
        _nextFaceCommand.attentionFocusX = 0.0f; // Centro/Baixo
        _nextFaceCommand.attentionFocusY = -0.5f; 
        return;
    }

    // Regra 2: Se detectou rosto e está curioso/sociável, foca no rosto
    if (_faceDetected) {
        if (state.curiosity > 0.3f) {
            _nextFaceCommand.attentionFocusX = _faceX;
            _nextFaceCommand.attentionFocusY = _faceY;
        } else {
            // Tédio: ignora o rosto propositalmente
            _nextFaceCommand.attentionFocusX = -_faceX; // Olha pro outro lado
            _nextFaceCommand.attentionFocusY = 0.0f;
        }
    } else {
        // Idle behavior: olhar aleatório ou centro
        _nextFaceCommand.attentionFocusX = 0.0f;
        _nextFaceCommand.attentionFocusY = 0.0f;
    }
}

FaceCommand BehaviorCoordinator::getLatestFaceCommand() {
    FaceCommand cmd = _nextFaceCommand;
    _nextFaceCommand.isValid = false; // Consome o comando
    return cmd;
}