#include "WifiSys.h"
#include "Actions.h"
#include "SDSys.h"
#include <ArduinoJson.h>

WebServer WifiSys::server(80);
Preferences WifiSys::pref;
bool WifiSys::isModoAP = false;
bool WifiSys::isConnected = false;

void WifiSys::iniciar() {
    Serial.println("[SYSTEM] Lendo configuracoes de Rede (NVS)...");
    
    // Abre a partição "rede" no NVS (false = modo de leitura e escrita)
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
        server.handleClient(); // Mantém o painel de configuração online
        return; 
    }

    // Lógica do Modo Normal (Cliente da sua rede)
    if (WiFi.status() == WL_CONNECTED) {
        if (!isConnected) {
            Serial.print("[OK] Wi-Fi Conectado! IP do NodeBot: ");
            Serial.println(WiFi.localIP());
            SDSys::gravarLog("Wi-Fi Conectado com sucesso.");
            
            // Ativa as rotas normais de controlo do robô
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
    pref.clear(); // Apaga tudo
    pref.end();
    Serial.println("[WIFI] Credenciais apagadas! Reinicie o robo para entrar no Modo AP.");
}

// =========================================================
// ROTAS DO MODO DE CONFIGURAÇÃO (AP)
// =========================================================
void WifiSys::paginaConfiguracao() {
    // Um HTML limpo e profissional para você digitar a senha no telemóvel
    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>NodeBot Setup</title><style>body{font-family:sans-serif; background:#222; color:#fff; padding:20px;}";
    html += "input{width:100%; padding:10px; margin:10px 0; border-radius:5px;}";
    html += "button{background:#00ff00; color:#000; padding:15px; width:100%; border:none; font-weight:bold; cursor:pointer;}</style></head><body>";
    html += "<h2>Configurar NodeBot</h2>";
    html += "<form action='/salvar' method='POST'>";
    html += "<label>Nome da sua Rede Wi-Fi (SSID):</label>";
    html += "<input type='text' name='ssid' required>";
    html += "<label>Senha do Wi-Fi:</label>";
    html += "<input type='password' name='pass' required>";
    html += "<button type='submit'>Salvar e Reiniciar</button>";
    html += "</form></body></html>";
    
    server.send(200, "text/html", html);
}

void WifiSys::salvarConfiguracao() {
    if (server.hasArg("ssid") && server.hasArg("pass")) {
        String novoSsid = server.arg("ssid");
        String novaPass = server.arg("pass");

        // Salva na memória blindada NVS
        pref.putString("ssid", novoSsid);
        pref.putString("pass", novaPass);

        String html = "<html><body style='background:#222; color:#0f0; font-family:sans-serif; text-align:center; margin-top:50px;'>";
        html += "<h2>Credenciais Salvas!</h2><p>O NodeBot vai reiniciar agora e conectar-se a " + novoSsid + ".</p>";
        html += "<p>Feche esta pagina.</p></body></html>";
        server.send(200, "text/html", html);

        Serial.println("[WIFI] Novas credenciais recebidas. Reiniciando em 2 segundos...");
        delay(2000);
        ESP.restart(); // Reinicia o hardware para aplicar as mudanças!
    } else {
        server.send(400, "text/plain", "Erro: Preencha todos os campos.");
    }
}

// =========================================================
// ROTAS DO MODO NORMAL (API)
// =========================================================
void WifiSys::paginaRoot() {
    server.send(200, "text/plain", "NodeBot OS: Operacional.");
}

void WifiSys::receberComando() {
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