#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// ---------------------------------------------------------------------
// Display (ST7789 - SPI) - Pinagem Blindada Fase 4
// ---------------------------------------------------------------------
namespace Display
{
    constexpr int PIN_MOSI  = 47;
    constexpr int PIN_SCLK  = 21;
    constexpr int PIN_CS    = 45;
    constexpr int PIN_DC    = 48; // (Cuidado com a balada do LED RGB embutido kkkk)
    constexpr int PIN_RST   = -1; // Ligado direto no 3V3 / EN
    constexpr int PIN_BL    = 2;  // TROCADO DO 16 PARA O 2! (O 16 é da Câmera)

    constexpr uint16_t WIDTH  = 240;
    constexpr uint16_t HEIGHT = 320;

    // Aumentamos a sua aposta: 80MHz para fluidez total!
    constexpr uint32_t SPI_FREQUENCY = 80000000; 
}

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7789  _panel_instance;
    lgfx::Bus_SPI       _bus_instance;
    lgfx::Light_PWM     _light_instance; // Adicionado para o seu PIN_BL!

public:
    LGFX() {
        { // --- CONFIGURAÇÃO SPI ---
            auto cfg = _bus_instance.config();
            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = Display::SPI_FREQUENCY;
            cfg.dma_channel = 1; // DMA Ativo!

            cfg.pin_sclk = Display::PIN_SCLK;
            cfg.pin_mosi = Display::PIN_MOSI;
            cfg.pin_miso = -1;
            cfg.pin_dc   = Display::PIN_DC;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        { // --- CONFIGURAÇÃO DO PAINEL ---
            auto cfg = _panel_instance.config();
            cfg.pin_cs       = Display::PIN_CS;
            cfg.pin_rst      = Display::PIN_RST;
            cfg.pin_busy     = -1;
            cfg.panel_width  = Display::WIDTH;
            cfg.panel_height = Display::HEIGHT;
            cfg.offset_x     = 0;
            cfg.offset_y     = 0;
            
            cfg.invert       = false;  // ST7789 costuma precisar de cores invertidas
            cfg.rgb_order    = false;

            _panel_instance.config(cfg);
        }

        { // --- CONFIGURAÇÃO DO BACKLIGHT (PWM) ---
            if (Display::PIN_BL >= 0) {
                auto cfg = _light_instance.config();
                cfg.pin_bl = Display::PIN_BL;
                cfg.invert = false; 
                cfg.freq   = 44100;    // Frequência do PWM
                cfg.pwm_channel = 7;   // Canal livre de PWM no ESP32
                _light_instance.config(cfg);
                _panel_instance.setLight(&_light_instance);
            }
        }

        setPanel(&_panel_instance);
    }
};