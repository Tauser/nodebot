#include "Imu.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

static Adafruit_MPU6050 mpu;
static float aceleracaoX = 0, aceleracaoY = 0, aceleracaoZ = 0;
static float offX = 0, offY = 0, offZ = 0;

bool ImuSys::iniciar() {
    Wire.begin(8, 9); // Ajuste para os pinos I2C da sua placa
    if (!mpu.begin()) {
        Serial.println("[ERRO] ImuSys: MPU6050 não encontrado.");
        return false;
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // Calibração de Elite: Define o que é o "centro" físico do seu robô
    Serial.println("[IMU] Calibrando...");
    float sumX = 0, sumY = 0, sumZ = 0;
    for(int i = 0; i < 50; i++) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        sumX += a.acceleration.x;
        sumY += a.acceleration.y;
        sumZ += a.acceleration.z;
        delay(5); // Delay seguro durante o setup
    }
    offX = sumX / 50.0;
    offY = sumY / 50.0;
    offZ = (sumZ / 50.0) - 9.81; // Desconta a gravidade
    
    Serial.println("[OK] ImuSys: Zerado e Online.");
    return true;
}

void ImuSys::atualizar() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    aceleracaoX = a.acceleration.x - offX;
    aceleracaoY = a.acceleration.y - offY;
    aceleracaoZ = a.acceleration.z - offZ;
}

bool ImuSys::isCaido() {
    return (abs(aceleracaoZ) < 5.0 && (abs(aceleracaoX) > 7.0 || abs(aceleracaoY) > 7.0));
}

bool ImuSys::isAgitado() {
    float forcaTotal = sqrt(pow(aceleracaoX, 2) + pow(aceleracaoY, 2) + pow(aceleracaoZ, 2));
    return (forcaTotal > 15.0); 
}