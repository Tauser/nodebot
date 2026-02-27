#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

class WifiSys {
public:
    static void iniciar();   // Mudou para void (não trava o boot)
    static void atualizar();
private:
    static WebServer server;
    static bool isConnected;
    static void setupRoutes();
    static void handleRoot();
    static void handleCommand();
};