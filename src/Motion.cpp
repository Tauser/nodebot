#include "Motion.h"

SMS_STS Motion::st;

bool Motion::iniciar() {
    Serial1.begin(1000000, SERIAL_8N1, SERVO_RX, SERVO_TX);
    st.pSerial = &Serial1;
    
    delay(500); // Estabilização do barramento

    // Fail-Fast: Se o hardware não responder, o boot falha
    if (!testarComunicacao()) {
        Serial.println("[ERRO] Motion: Servos não respondem no ID 1 ou 2!");
        return false;
    }

    st.EnableTorque(1, 1);
    st.EnableTorque(2, 1);
    centralizar();
    
    Serial.println("[OK] Motion: Barramento 1Mbps validado.");
    return true;
}

bool Motion::testarComunicacao() {
    // Tenta ler a voltagem do servo ID 1. Se retornar -1, falhou.
    int v = st.ReadVoltage(1);
    return (v != -1);
}

void Motion::atualizar(SystemState estadoAtual) {
    // Se o sistema entrar em paragem crítica, cortamos o torque
    if (estadoAtual == STATE_CRITICAL_STOP) {
        relaxar();
    }
}

void Motion::olharPara(int pan, int tilt, int vel, int acc) {
    int sPan = constrain(pan, PAN_MIN, PAN_MAX);
    int sTilt = constrain(tilt, TILT_MIN, TILT_MAX);

    // Envio robusto individual
    st.WritePosEx(1, sPan, vel, acc);
    st.WritePosEx(2, sTilt, vel, acc);
}

void Motion::relaxar() {
    st.EnableTorque(1, 0);
    st.EnableTorque(2, 0);
}

void Motion::centralizar() {
    olharPara(2048, 2048, 400, 20);
}