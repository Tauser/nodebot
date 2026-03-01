#pragma once
#include "services/face/FaceService.h" 
#include "ai/AdaptiveModel.h"
#include "ai/EmotionModel.h"

struct InternalState {
    float energy;      
    float curiosity;   
    float stimulation; 
    Emotion currentEmotion;
};

class PersonalityService {
public:
    void init(AdaptiveModel* adaptiveModel);
    void update(uint32_t deltaMs);
    void addStimulus(float intensity);
    void expendEnergy(float amount);
    void rest(float amount);
    const InternalState& getState() const;

private:
    InternalState _state;
    AdaptiveModel* _adaptiveModel;
    EmotionModel _emotionModel; 
    void evaluateEmotion(); 
};