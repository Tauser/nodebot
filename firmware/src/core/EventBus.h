#pragma once
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

enum class SystemEvent {
    TOUCH_TAP,
    TOUCH_PETTING,
    LOUD_NOISE,
    FACE_DETECTED,
    BATTERY_LOW
};

struct EventMessage {
    SystemEvent type;
    float payload; // Um valor genérico (ex: intensidade do som)
};

class EventBus {
public:
    void init();
    
    // Qualquer serviço pode publicar um evento
    void publish(SystemEvent event, float payload = 0.0f);
    
    // O BehaviorCoordinator ou o ReflexEngine consomem os eventos
    bool consume(EventMessage& outMsg);

private:
    QueueHandle_t _eventQueue;
};

// Singleton global para acesso fácil em qualquer ficheiro
extern EventBus Bus;