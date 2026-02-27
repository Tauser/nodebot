#include "WifiSys.h"
#include "Actions.h"
#include "Display.h"

// Configurações de Rede (Ajusta depois no Config.h)
const char* ssid = "NOME_DA_TUA_REDE";
const char* password = "SENHA_DA_TUA_REDE";

WebServer WifiSys::server(80);

bool WifiSys::iniciar() {
    Serial.printf("[WIFI] Conectando a %s...\n", ssid);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Espera até 10 segundos para conectar
    int tentativas = 0;
    while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
        delay(500);
        Serial.print(".");
        tentativas++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[OK] WiFi Conectado!");
        Serial.print("[SYSTEM] IP do NodeBot: ");
        Serial.println(WiFi.localIP());
        
        setupRoutes();
        server.begin();
        return true;
    }

    Serial.println("\n[ERRO] WiFi: Falha ao conectar. Iniciando em modo Offline.");
    return false;
}

void WifiSys::setupRoutes() {
    server.on("/", HTTP_GET, handleRoot);
    server.on("/cmd", HTTP_POST, handleCommand);
}

void WifiSys::handleRoot() {
    server.send(200, "text/plain", "NodeBot OS Online. Pronto para comandos.");
}

void WifiSys::handleCommand() {
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, body);

        if (!error) {
            const char* acao = doc["action"];
            
            if (strcmp(acao, "sim") == 0) Actions::dizerSim();
            else if (strcmp(acao, "nao") == 0) Actions::dizerNao();
            else if (strcmp(acao, "curioso") == 0) Actions::olharCurioso();
            
            server.send(200, "application/json", "{\"status\":\"ok\"}");
            return;
        }
    }
    server.send(400, "application/json", "{\"status\":\"error\"}");
}

void WifiSys::atualizar() {
    server.handleClient();
}