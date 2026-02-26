# 🤖 NodeBot

> Um assistente pessoal robótico de alta performance, inspirado no ecossistema Stack-chan, mas com uma arquitetura de hardware totalmente customizada e modular.

O projeto **NodeBot** nasce da necessidade de libertar o design original das amarras de hardwares fechados. Em vez de utilizar blocos comerciais pré-fabricados, este robô é construído a partir de componentes individuais, permitindo total controlo sobre o código, a mecânica e a eletrónica.

## ⚙️ Arquitetura de Hardware (A.K.A. "Tanque de Guerra")

- **Cérebro:** Freenove ESP32-S3 WROOM (N16R8 - 16MB Flash / 8MB PSRAM)
- **Rosto:** Ecrã IPS de 2 polegadas (Comunicação SPI)
- **Músculos:** Servos Seriais Feetech SCS0009
- **Voz:** Amplificador de Áudio I2S MAX98357A
- **Energia:** Módulo SW6106 (Carregamento Bidirecional USB-C)

## 💻 Ambiente de Desenvolvimento

Desenvolvido em **C/C++** utilizando o **PlatformIO** no VS Code, com otimizações específicas de partições de memória e ativação de barramento OPI para o chip N16R8.
