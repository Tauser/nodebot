#include "Display.h"

TFT_eSPI Display::tft = TFT_eSPI();
TFT_eSprite Display::canvas = TFT_eSprite(&tft);
unsigned long Display::proximoPiscar = 0;
RobotEmotion Display::emocaoAtual = EMOCAO_NEUTRO;
bool Display::isPiscando = false;

bool Display::iniciar() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    canvas.setColorDepth(16);
    
    // Fail-Fast: Se não houver PSRAM, o ecrã não liga
    if (canvas.createSprite(tft.width(), tft.height()) == NULL) {
        Serial.println("[FATAL] Display: Falha ao alocar PSRAM!");
        return false;
    }
    
    proximoPiscar = millis() + 2000;
    return true;
}

void Display::definirEmocao(RobotEmotion novaEmocao) {
    emocaoAtual = novaEmocao;
}

void Display::atualizar(SystemState estadoAtual) {
    unsigned long agora = millis();
    canvas.fillSprite(TFT_BLACK); // Limpa o frame

    uint32_t cor = TFT_CYAN;

    // 1. Sobrescrita de Saúde (O Sistema fala mais alto que a Emoção)
    if (estadoAtual == STATE_CRITICAL_STOP) {
        // Robô "morreu" (Bateria < 5%) - Ignora emoção, desenha X
        canvas.drawLine(POS_X_ESQ, POS_Y, POS_X_ESQ + OLHO_LARGURA, POS_Y + OLHO_ALTURA, TFT_RED);
        canvas.drawLine(POS_X_ESQ + OLHO_LARGURA, POS_Y, POS_X_ESQ, POS_Y + OLHO_ALTURA, TFT_RED);
        canvas.drawLine(POS_X_DIR, POS_Y, POS_X_DIR + OLHO_LARGURA, POS_Y + OLHO_ALTURA, TFT_RED);
        canvas.drawLine(POS_X_DIR + OLHO_LARGURA, POS_Y, POS_X_DIR, POS_Y + OLHO_ALTURA, TFT_RED);
        renderizar();
        return;
    } 
    else if (estadoAtual == STATE_RECOVERY) {
        cor = TFT_ORANGE;
        emocaoAtual = EMOCAO_CANSADO; // Força emoção de cansaço
    }

    // 2. Lógica Autônoma de Piscar (Blink)
    if (agora > proximoPiscar) {
        isPiscando = true;
        if (agora > proximoPiscar + 150) { // O piscar dura 150ms
            isPiscando = false;
            proximoPiscar = agora + random(2000, 6000);
        }
    }

    // 3. Renderização Procedural (Camada Base)
    desenharOlhoBase(POS_X_ESQ, POS_Y, cor);
    desenharOlhoBase(POS_X_DIR, POS_Y, cor);

    // 4. Aplicação das Máscaras de Emoção
    if (!isPiscando) {
        aplicarMascara(POS_X_ESQ, POS_Y, emocaoAtual, true);
        aplicarMascara(POS_X_DIR, POS_Y, emocaoAtual, false);
    } else {
        // Máscara de Piscar (Cobre 90% do olho de cima para baixo)
        canvas.fillRect(POS_X_ESQ - 5, POS_Y - 5, OLHO_LARGURA + 10, OLHO_ALTURA - 10, TFT_BLACK);
        canvas.fillRect(POS_X_DIR - 5, POS_Y - 5, OLHO_LARGURA + 10, OLHO_ALTURA - 10, TFT_BLACK);
    }

    renderizar();
}

void Display::desenharOlhoBase(int x, int y, uint32_t cor) {
    canvas.fillRoundRect(x, y, OLHO_LARGURA, OLHO_ALTURA, RAIO_CURVATURA, cor);
}

void Display::aplicarMascara(int x, int y, RobotEmotion emocao, bool olhoEsquerdo) {
    // Adicionamos uma margem de segurança na máscara para cortar limpo
    int mX = x - 5; 
    int mL = OLHO_LARGURA + 10;

    switch (emocao) {
        case EMOCAO_FELIZ:
            // Bochechas sobem e cobrem a base do olho (sorriso com os olhos)
            canvas.fillRect(mX, y + (OLHO_ALTURA / 2) + 10, mL, OLHO_ALTURA / 2, TFT_BLACK);
            // Curva a máscara para não ficar um corte 100% reto
            canvas.fillCircle(x + (OLHO_LARGURA/2), y + OLHO_ALTURA, 20, TFT_BLACK); 
            break;

        case EMOCAO_CANSADO:
            // Pálpebra superior desce até à metade, de forma reta
            canvas.fillRect(mX, y - 5, mL, OLHO_ALTURA / 2, TFT_BLACK);
            break;

        case EMOCAO_ZANGADO:
            // Corte diagonal. O lado de dentro do olho fica mais baixo (franzir sobrolho)
            if (olhoEsquerdo) {
                // Triângulo: Topo-Esq, Topo-Dir(mais baixo), Fundo-Dir(ponto extra fora)
                canvas.fillTriangle(mX, y-10, mX + mL, y + 40, mX + mL, y-10, TFT_BLACK);
            } else {
                // Oposto para o olho direito
                canvas.fillTriangle(mX, y + 40, mX + mL, y-10, mX, y-10, TFT_BLACK);
            }
            break;

        case EMOCAO_TRISTE:
            // Oposto de zangado. O lado de fora cai (olhar pidão)
            if (olhoEsquerdo) {
                canvas.fillTriangle(mX, y + 30, mX + mL, y-10, mX, y-10, TFT_BLACK);
            } else {
                canvas.fillTriangle(mX, y-10, mX + mL, y + 30, mX + mL, y-10, TFT_BLACK);
            }
            break;

        case EMOCAO_NEUTRO:
        default:
            // Nenhuma máscara é aplicada
            break;
    }
}

void Display::renderizar() {
    canvas.pushSprite(0, 0);
}