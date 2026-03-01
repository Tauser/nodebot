#pragma once

#include <stdint.h>

/*
|--------------------------------------------------------------------------
| NodeBot Hardware Configuration
|--------------------------------------------------------------------------
| Target MCU: ESP32-S3 WROOM (Freenove)
| Hardware Version: v1.0
| Status: FROZEN
|--------------------------------------------------------------------------
*/

namespace Hardware
{
    // ---------------------------------------------------------------------
    // Hardware Version
    // ---------------------------------------------------------------------
    constexpr const char* VERSION = "v1.0";

    // ---------------------------------------------------------------------
    // CPU & System
    // ---------------------------------------------------------------------
    constexpr uint32_t CPU_FREQUENCY_HZ = 240000000;
    constexpr bool PSRAM_ENABLED = true;

    // ---------------------------------------------------------------------
    // Display (ST7789 - SPI)
    // ---------------------------------------------------------------------
    namespace Display
    {
        constexpr int PIN_MOSI  = 47;
        constexpr int PIN_SCLK  = 21;
        constexpr int PIN_CS    = 45;
        constexpr int PIN_DC    = 48;
        constexpr int PIN_RST   = -1; // Ligado ao pino EN da placa
        constexpr int PIN_BL    = 16; // Opcional: Pino livre para PWM do Backlight

        constexpr uint16_t WIDTH  = 240;
        constexpr uint16_t HEIGHT = 320;

        constexpr uint32_t SPI_FREQUENCY = 40000000; // 40MHz para alto FPS
    }

    // ---------------------------------------------------------------------
    // Camera (OV2640 - Pinos Fixos da Freenove)
    // ---------------------------------------------------------------------
    namespace Camera
    {
        constexpr bool ENABLED = true;
        
        constexpr int PIN_XCLK  = 15;
        constexpr int PIN_PCLK  = 13;
        constexpr int PIN_VSYNC = 6;
        constexpr int PIN_HREF  = 7;
        
        constexpr int PIN_Y9    = 16;
        constexpr int PIN_Y8    = 17;
        constexpr int PIN_Y7    = 18;
        constexpr int PIN_Y6    = 12;
        constexpr int PIN_Y5    = 10;
        constexpr int PIN_Y4    = 8;
        constexpr int PIN_Y3    = 9;
        constexpr int PIN_Y2    = 11;

        constexpr int FRAME_WIDTH  = 320; // QVGA
        constexpr int FRAME_HEIGHT = 240;
        constexpr int JPEG_QUALITY = 12;
    }

    // ---------------------------------------------------------------------
    // Audio Output (MAX98357A - I2S 0)
    // ---------------------------------------------------------------------
    namespace AudioOut
    {
        // Movido para os pinos 41, 42 e 43 para fugir da Câmera e I2C
        constexpr int PIN_BCLK  = 41;
        constexpr int PIN_LRCK  = 42;
        constexpr int PIN_DATA  = 43;

        constexpr uint32_t SAMPLE_RATE = 44100;
        constexpr uint8_t BITS_PER_SAMPLE = 16;
    }

    // ---------------------------------------------------------------------
    // Microphone (INMP441 - I2S 1)
    // ---------------------------------------------------------------------
    namespace AudioIn
    {
        // Usando pinos seguros ADC/RTC livres de conflitos
        constexpr int PIN_BCLK  = 35; 
        constexpr int PIN_LRCK  = 36;
        constexpr int PIN_DATA  = 37;

        constexpr uint32_t SAMPLE_RATE = 16000; // Ideal para STT/Voice Recognition
    }

    // ---------------------------------------------------------------------
    // Smart Servos (Feetech/STS - Serial 1)
    // ---------------------------------------------------------------------
    namespace Servo
    {
        constexpr int PIN_RX    = 3;
        constexpr int PIN_TX    = 1;
        
        constexpr uint32_t BAUD_RATE = 1000000; // Padrão dos servos Feetech
        
        constexpr int ID_HEAD_PAN  = 1;
        constexpr int ID_HEAD_TILT = 2;
    }

    // ---------------------------------------------------------------------
    // Sensores Internos e I2C (IMU MPU6050)
    // ---------------------------------------------------------------------
    namespace Sensors
    {
        // I2C
        constexpr int PIN_I2C_SDA = 4;
        constexpr int PIN_I2C_SCL = 5;

        // Touch
        constexpr int PIN_TOUCH = 14;
        constexpr int TOUCH_THRESHOLD = 30000;

        // Energia/LED
        constexpr int PIN_BATTERY_ADC = 19;
        constexpr int PIN_LED_DATA = 2;
        constexpr int NUM_LEDS = 2;
    }

    // ---------------------------------------------------------------------
    // SD Card (SD_MMC Interno)
    // ---------------------------------------------------------------------
    namespace SDCard
    {
        constexpr int PIN_CMD = 38;
        constexpr int PIN_CLK = 39;
        constexpr int PIN_D0  = 40;
    }

    // ---------------------------------------------------------------------
    // WiFi
    // ---------------------------------------------------------------------
    namespace Network
    {
        constexpr bool WIFI_ENABLED = true;
    }

} // namespace Hardware