#pragma once
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class SDSys {
public:
    static bool iniciar();
    static void gravarLog(const char* evento);

private:
    static const int PINO_CS = 10; 
};