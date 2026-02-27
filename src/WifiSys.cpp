#include "WifiSys.h"
#include "Actions.h"
#include "SDSys.h"
#include "Display.h"
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <LittleFS.h>

WebServer WifiSys::server(80);
Preferences WifiSys::pref;
bool WifiSys::isModoAP = false;
bool WifiSys::isConnected = false;

void WifiSys::iniciar() {
    Serial.println("[SYSTEM] Lendo configuracoes de Rede (NVS)...");
    
    pref.begin("rede", false); 
    String redeSalva = pref.getString("ssid", "");
    String senhaSalva = pref.getString("pass", "");

    if (redeSalva == "") {
        Serial.println("[WIFI] Nenhuma rede salva. Entrando em Modo AP (Setup)...");
        iniciarModoAP();
    } else {
        Serial.printf("[WIFI] Rede encontrada: %s. Conectando em background...\n", redeSalva.c_str());
        iniciarModoSTA(redeSalva, senhaSalva);
    }
}

void WifiSys::iniciarModoAP() {
    isModoAP = true;
    WiFi.mode(WIFI_AP);
    WiFi.softAP("NodeBot_Setup", "12345678"); 
    
    Serial.print("[OK] Modo AP Ativo! Conecte-se a 'NodeBot_Setup' e acesse o IP: ");
    Serial.println(WiFi.softAPIP());

    SDSys::gravarLog("Wi-Fi: Entrou em Modo de Configuracao (AP).");

    Display::ativarQR("WIFI:S:NodeBot_Setup;T:WPA;P:12345678;;");

    server.on("/", HTTP_GET, paginaConfiguracao);
    server.on("/salvar", HTTP_POST, salvarConfiguracao);
    server.begin();
}

void WifiSys::iniciarModoSTA(String ssid, String pass) {
    isModoAP = false;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());
}

void WifiSys::atualizar() {
    if (isModoAP) {
        server.handleClient(); 
        return; 
    }

    if (WiFi.status() == WL_CONNECTED) {
        if (!isConnected) {
            Serial.print("[OK] Wi-Fi Conectado! IP do NodeBot: ");
            Serial.println(WiFi.localIP());
            
            if (MDNS.begin("nodebot")) {
                Serial.println("[OK] mDNS Ativo! Acesse: http://nodebot.local no seu navegador.");
            } else {
                Serial.println("[ERRO] Falha ao iniciar o servico mDNS.");
            }

            SDSys::gravarLog("Wi-Fi Conectado com sucesso.");
            
            String urlPainel = "http://" + WiFi.localIP().toString();
            Display::ativarQR(urlPainel);

            server.on("/", HTTP_GET, paginaRoot);
            server.on("/api/acao", HTTP_POST, receberComando);
            server.begin();
            isConnected = true;
        }
        server.handleClient();
    } else {
        if (isConnected) {
            Serial.println("[AVISO] Wi-Fi Desconectado. A tentar reconectar...");
            SDSys::gravarLog("Alerta: Conexao Wi-Fi perdida.");
            isConnected = false;
        }
    }
}

void WifiSys::apagarCredenciais() {
    pref.begin("rede", false);
    pref.clear(); 
    pref.end();
    Serial.println("[WIFI] Credenciais apagadas! Reinicie o robo para entrar no Modo AP.");
}

void WifiSys::paginaConfiguracao() {
    Display::desativarQR(); 

    if (LittleFS.exists("/setup.html")) {
        File file = LittleFS.open("/setup.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    } else {
        server.send(500, "text/plain", "Erro 500: Ficheiro /setup.html em falta na memoria LittleFS.");
    }
}

void WifiSys::salvarConfiguracao() {
    if (server.hasArg("ssid") && server.hasArg("pass")) {
        String novoSsid = server.arg("ssid");
        String novaPass = server.arg("pass");

        pref.putString("ssid", novoSsid);
        pref.putString("pass", novaPass);

        String html = "<html><body style='background:#121212; color:#0f0; font-family:sans-serif; text-align:center; margin-top:50px;'>";
        html += "<h2>Credenciais Salvas!</h2><p>O NodeBot vai reiniciar e conectar-se a " + novoSsid + ".</p>";
        html += "<p>Acesse <a href='http://nodebot.local' style='color:#0ff;'>http://nodebot.local</a> daqui a uns segundos.</p></body></html>";
        server.send(200, "text/html", html);

        Serial.println("[WIFI] Novas credenciais recebidas. Reiniciando em 2 segundos...");
        delay(2000);
        ESP.restart(); 
    } else {
        server.send(400, "text/plain", "Erro: Preencha todos os campos.");
    }
}

void WifiSys::paginaRoot() {
    Display::desativarQR();

    if (LittleFS.exists("/index.html")) {
        File file = LittleFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    } else {
        server.send(500, "text/plain", "Erro 500: Ficheiro /index.html em falta na memoria LittleFS.");
    }
}

void WifiSys::receberComando() {
    Display::desativarQR();

    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, body);

        if (!error) {
            const char* comando = doc["comando"];
            Serial.printf("[REDE] Comando Remoto Recebido: %s\n", comando);
            
            if (strcmp(comando, "sim") == 0) Actions::dizerSim();
            else if (strcmp(comando, "nao") == 0) Actions::dizerNao();
            else if (strcmp(comando, "curioso") == 0) Actions::olharCurioso();
            else if (strcmp(comando, "susto") == 0) Actions::reagirASusto();
            else if (strcmp(comando, "carinho") == 0) Actions::reagirACarinho();
            
            server.send(200, "application/json", "{\"status\":\"sucesso\"}");
            return;
        }
    }
    server.send(400, "application/json", "{\"status\":\"erro\"}");
}