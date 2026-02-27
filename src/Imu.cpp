#include "Imu.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Escondemos o MPU6050 e as variáveis aqui, longe dos olhos do main.cpp!
static Adafruit_MPU6050 mpu;
static float aceleracaoX = 0;
static float aceleracaoY = 0;
static float aceleracaoZ = 0;

bool ImuSys::iniciar() {
    Wire.begin(8, 9); // Pinos I2C: SDA=8, SCL=9

    if (!mpu.begin()) {
        Serial.println("[ERRO] ImuSys: MPU6050 não encontrado! Verifique a fiação.");
        return false;
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println("[OK] ImuSys: Acelerómetro e Giroscópio online.");
    return true;
}

void ImuSys::atualizar() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    aceleracaoX = a.acceleration.x;
    aceleracaoY = a.acceleration.y;
    aceleracaoZ = a.acceleration.z;
}

bool ImuSys::isCaido() {
    return (abs(aceleracaoZ) < 5.0 && (abs(aceleracaoX) > 7.0 || abs(aceleracaoY) > 7.0));
}

bool ImuSys::isAgitado() {
    float forcaTotal = sqrt(pow(aceleracaoX, 2) + pow(aceleracaoY, 2) + pow(aceleracaoZ, 2));
    return (forcaTotal > 15.0); 
}