#include "WifiSys.h"
#include "Actions.h"

WebServer WifiSys::server(80);
bool WifiSys::isConnected = false;

// Ajuste com os dados da sua rede
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";

void WifiSys::iniciar() {
    Serial.println("[WIFI] Iniciando antena em background...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    // REMOVIDO o while() que travava o robô. O boot segue imediatamente!
}

void WifiSys::atualizar() {
    // Máquina de estados simples para gerir a conexão sem travar o RTOS
    if (WiFi.status() == WL_CONNECTED) {
        if (!isConnected) {
            Serial.println("\n[OK] WiFi Conectado!");
            Serial.print("[SYSTEM] IP: ");
            Serial.println(WiFi.localIP());
            
            if (MDNS.begin("nodebot")) {
                Serial.println("[OK] MDNS: Acesse http://nodebot.local");
            }
            setupRoutes();
            server.begin();
            isConnected = true;
        }
        server.handleClient(); // Processa comandos web
    } else {
        if (isConnected) {
            Serial.println("[AVISO] WiFi Desconectado. O robô continua operando offline.");
            isConnected = false;
        }
    }
}

void WifiSys::setupRoutes() {
    server.on("/", HTTP_GET, handleRoot);
    server.on("/cmd", HTTP_POST, handleCommand);
}

void WifiSys::handleRoot() {
    server.send(200, "text/plain", "NodeBot OS Online.");
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
            else if (strcmp(acao, "susto") == 0) Actions::reagirASusto();
            
            server.send(200, "application/json", "{\"status\":\"ok\"}");
            return;
        }
    }
    server.send(400, "application/json", "{\"status\":\"error\"}");
}