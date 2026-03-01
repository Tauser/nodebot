#include "EventBus.h"

EventBus Bus; // Instância global

void EventBus::init() {
    // Cria uma fila segura para 20 mensagens simultâneas
    _eventQueue = xQueueCreate(20, sizeof(EventMessage));
}

void EventBus::publish(SystemEvent event, float payload) {
    if (_eventQueue == nullptr) return;

    EventMessage msg;
    msg.type = event;
    msg.payload = payload;

    // Envia a mensagem. Se a fila estiver cheia, desiste imediatamente (não bloqueia)
    xQueueSend(_eventQueue, &msg, 0);
}

bool EventBus::consume(EventMessage& outMsg) {
    if (_eventQueue == nullptr) return false;

    // Tenta ler uma mensagem. Retorna true se conseguiu.
    return (xQueueReceive(_eventQueue, &outMsg, 0) == pdTRUE);
}