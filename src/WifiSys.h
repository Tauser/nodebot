#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>

class WifiSys {
public:
    static void iniciar();
    static void atualizar();
    static void apagarCredenciais(); 

private:
    static WebServer server;
    static Preferences pref;
    static bool isModoAP;
    static bool isConnected;

    static void iniciarModoAP();
    static void iniciarModoSTA(String ssid, String pass);

    static void paginaConfiguracao();
    static void salvarConfiguracao();

    static void paginaRoot();
    static void receberComando();
};