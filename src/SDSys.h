#pragma once
#include <Arduino.h>
#include <SD_MMC.h> 

class SDSys {
public:
    static bool iniciar();
    static void gravarLog(const char* evento);
};