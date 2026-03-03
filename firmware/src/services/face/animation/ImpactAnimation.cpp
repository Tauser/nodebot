#include "ImpactAnimation.h"

void ImpactAnimation::update(EyeModel& model, float dt) {
    if (impactIntensity > 0.01f) {
        // Os olhos esticam verticalmente com o susto
        float bounce = impactIntensity * 0.4f;
        model.leftScaleY += bounce;
        model.rightScaleY += bounce;

        // Amortecimento suave
        impactIntensity -= 6.0f * dt;
        if (impactIntensity < 0) impactIntensity = 0;
    }
}