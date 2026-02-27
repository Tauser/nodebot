# 🤖 NodeBot OS

Bem-vindo ao código-fonte do **NodeBot**, um sistema operativo robótico de tempo real (RTOS) construído sobre a arquitetura dual-core do ESP32-S3.

Este projeto foca-se em interações de alto desempenho, combinando processamento de visão nativo (DMA/PSRAM), animações procedurais ("Saccades" e respiração de motores), áudio de alta fidelidade via I2S, e um sistema de reflexos instintivos.

---

## ⚙️ Arquitetura de Hardware

A "Placa Mãe" deste robô é a **Freenove ESP32-S3-WROOM CAM**. Devido à câmara embutida e ao slot SD_MMC de alta velocidade, o mapeamento de pinos exige extrema precisão para evitar colisões lógicas.

### 📋 Lista de Materiais (BOM)

- **Cérebro/Visão:** Freenove ESP32-S3-WROOM CAM (8MB PSRAM, Câmera OV2640).
- **Display (Rosto):** Ecrã TFT LCD (Controlador ST7789 ou ILI9341).
- **Músculos:** Servos Feetech (Comunicação Serial RS485/UART).
- **Sistema Vestibular:** Módulo MPU6050 (Acelerómetro e Giroscópio).
- **Cordas Vocais:** Amplificador de Áudio MAX98357A (I2S).
- **Tato:** Fita de cobre capacitiva.

---

## 🔌 Matriz de Ligações (Pinout Definitivo)

> **⚠️ AVISO CRÍTICO DE ENERGIA:** Os motores Feetech exigem alta corrente. **NUNCA** os alimente diretamente através do pino 5V/3V3 da placa Freenove. Utilize um conversor Step-Down dedicado (ou bateria apropriada) para os motores, ligando apenas os cabos de Sinal (TX/RX) e o cabo **GND (Terra)** em comum com o ESP32.

| Módulo                | Pino ESP32-S3 | Função / Ligação | Notas                               |
| :-------------------- | :------------ | :--------------- | :---------------------------------- |
| **Motores (Feetech)** | `GPIO 1`      | TX               | Serial 1 (1 Mbps)                   |
|                       | `GPIO 3`      | RX               | Serial 1 (1 Mbps)                   |
| **I2C (MPU6050)**     | `GPIO 4`      | SDA              | Partilhado com a Câmera             |
|                       | `GPIO 5`      | SCL              | Partilhado com a Câmera             |
| **Áudio (MAX98357A)** | `GPIO 35`     | BCLK / BCL       | Barramento I2S                      |
|                       | `GPIO 36`     | LRC / WSEL       | Barramento I2S                      |
|                       | `GPIO 37`     | DOUT / DIN       | Barramento I2S                      |
| **Tato (Capacitivo)** | `GPIO 14`     | TOUCH            | Ligar à fita de cobre               |
| **Luzes & Energia**   | `GPIO 41`     | LED              | LED Indicador de Estado             |
|                       | `GPIO 19`     | ADC              | Leitura de Bateria (Divisor Tensão) |

### 📺 Configuração Especial do Ecrã (TFT_eSPI)

Os pinos do ecrã não estão no `Config.h`. Devem ser configurados **exclusivamente** no ficheiro `User_Setup.h` da biblioteca `TFT_eSPI`:

- `TFT_MOSI` -> **47**
- `TFT_SCLK` -> **21**
- `TFT_CS` -> **45**
- `TFT_DC` -> **48**
- `TFT_RST` -> **2**

---

## 🧠 Arquitetura de Software (FreeRTOS)

O sistema está dividido nativamente nos dois núcleos do chip para garantir que cálculos pesados não atrasem os reflexos físicos.

- **Core 1 (`TaskHardware` - 50Hz):** Trata das operações em tempo real restrito. Atualiza o ecrã com as expressões faciais, processa as curvas de suavização dos motores Feetech e esvazia o buffer de áudio I2S.
- **Core 0 (`TaskTelemetry` - 20Hz):** O sistema instintivo. Lê o acelerómetro para detetar quedas, filtra o ruído do sensor capacitivo (tato) e monitoriza a bateria. Desencadeia as emoções imediatamente.
- **Core 0 (`TaskBrain` - 10Hz):** Operações pesadas e assíncronas. Gere o Servidor Web embutido (UI remota via LittleFS) e o sistema de ficheiros nativos.

---

## 🚀 Como Fazer o Deploy (Guia de Arranque)

1. **Configurar o PlatformIO:** Certifique-se de que o `platformio.ini` tem a flag `-D BOARD_HAS_PSRAM` ativada.
2. **Carregar o Front-End (LittleFS):** \* Coloque os ficheiros `index.html` e `setup.html` na pasta `/data`.
   - No VS Code, clique no ícone do PlatformIO -> `esp32-s3-devkitc-1` -> `Platform` -> **`Build Filesystem Image`** e depois **`Upload Filesystem Image`**.
3. **Preparar o Cartão SD:**
   - Formate o MicroSD em FAT32.
   - Coloque os ficheiros de áudio `.mp3` na raiz do cartão (ex: `feliz.mp3`, `susto.mp3`, `sim.mp3`, `nao.mp3`, `curioso.mp3`).
4. **Carregar o Cérebro:** Compile e faça o _Upload_ normal do código C++.

---

_Construído com sangue, suor e compilações bem-sucedidas._
