#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "../include/Config.h"

class WifiSys {
public:
    static bool iniciar();
    static void atualizar(); // Deve rodar na TaskBrain (Core 0)
    
private:
    static WebServer server;
    static void handleRoot();
    static void handleCommand(); // Onde processamos ordens do PC
    static void setupRoutes();
};