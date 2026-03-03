#pragma once

#include "../services/PersonalityService.h"

// Estrutura de comando para o FaceService (conforme especificado)
struct FaceCommand {
    Emotion emotion;
    float attentionFocusX;
    float attentionFocusY;
    bool isValid; // Flag para saber se há um novo comando
};

class BehaviorCoordinator {
public:
    BehaviorCoordinator();

    // Recebe o estado atual e decide o próximo passo
    void arbitrate(const InternalState& state);

    // Retorna o comando decidido para a face
    FaceCommand getLatestFaceCommand();

    // Métodos para receber inputs sensoriais (simplificado)
    void setFaceDetected(bool detected, float x, float y);

private:
    FaceCommand _nextFaceCommand;
    bool _faceDetected;
    float _faceX, _faceY;
};