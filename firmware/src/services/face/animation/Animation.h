#pragma once
#include "../model/EyeModel.h"

class Animation {
public:
    virtual ~Animation() {}
    virtual void update(EyeModel& model, float dt) = 0;
};