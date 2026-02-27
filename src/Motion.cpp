#include "Motion.h"

SMS_STS Motion::st;
int Motion::alvoX = 2048; // Centro padrão dos motores Feetech
int Motion::alvoY = 2048;

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

// Dentro do seu Motion.cpp, na função atualizar():

void Motion::atualizar(SystemState state) {
    if (state == STATE_CRITICAL_STOP || state == STATE_SLEEPING) {
        relaxar();
        return;
    }

    // Calcula os alvos dinâmicos
    int alvoAtualX = alvoX;
    int alvoAtualY = alvoY;

    // A MÁGICA DA RESPIRAÇÃO
    if (state == STATE_IDLE) {
        // Usa a função sin() com millis() para criar uma curva suave e perpétua.
        // O divisor 600.0 dita a velocidade (frequência).
        // O multiplicador 30 dita a força da respiração (amplitude em passos de servo).
        int compensacaoRespiracao = sin(millis() / 600.0) * 30; 
        
        // Aplica a respiração apenas no eixo Y (Cima/Baixo)
        alvoAtualY += compensacaoRespiracao;
    }

    // Daqui para baixo, o código mantém-se igual, enviando 
    // os valores alvoAtualX e alvoAtualY para os servos Feetech...
}

void Motion::olharPara(int pan, int tilt, int vel, int acc) {
    int sPan = constrain(pan, PAN_MIN, PAN_MAX);
    int sTilt = constrain(tilt, TILT_MIN, TILT_MAX);

    // MEMÓRIA DO SISTEMA: Guarda a base para a "respiração" saber onde estamos
    alvoX = sPan; 
    alvoY = sTilt;

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

