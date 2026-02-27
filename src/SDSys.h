#pragma once
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class SDSys {
public:
    static bool iniciar();
    static void gravarLog(const char* evento);

private:
    // PINO CS (Chip Select) DO LEITOR SD. 
    // Ajuste este número para o pino físico onde ligou o CS no ESP32-S3!
    static const int PINO_CS = 10; 
};