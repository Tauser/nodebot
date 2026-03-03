#pragma once

enum class EventType {
    NONE,
    LOUD_NOISE,
    INTERACTION_POSITIVE,
    SILENCE
};

class LocalClassifier {
public:
    bool classifyAudio(float volume, EventType& detectedType);
};