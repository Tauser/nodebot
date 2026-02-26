#include "Motion.h"

// Instancia o controlador
SMS_STS Motion::st;

void Motion::iniciar() {
    // Inicializa a Serial1 com a velocidade padrão dos Feetech (1.000.000 bps)
    // Sim, esses servos são MUITO rápidos na comunicação!
    Serial1.begin(1000000, SERIAL_8N1, SERVO_RX, SERVO_TX);
    st.pSerial = &Serial1;
    
    delay(500); // Aguarda a eletrônica estabilizar
    centralizar();
}

void Motion::olharPara(int pan, int tilt) {
    // IDs padrão: 1 para a base (Pan), 2 para o pescoço (Tilt)
    // Velocidade: 1000, Aceleração: 50
    st.WritePosEx(1, pan, 1000, 50); 
    st.WritePosEx(2, tilt, 1000, 50);
}

void Motion::centralizar() {
    olharPara(2048, 2048); // 2048 é geralmente o centro (0-4095)
}

void Motion::relaxar() {
    st.unLockEprom(1); // Libera o motor 1
    st.unLockEprom(2); // Libera o motor 2
}