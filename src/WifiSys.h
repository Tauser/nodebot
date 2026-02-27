#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

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

    // Métodos de Arranque
    static void iniciarModoAP();
    static void iniciarModoSTA(String ssid, String pass);

    // Rotas do Modo AP
    static void paginaConfiguracao();
    static void salvarConfiguracao();

    // Rotas do Modo STA
    static void paginaRoot();
    static void receberComando();
};