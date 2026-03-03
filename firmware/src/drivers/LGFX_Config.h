#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ILI9341 _panel_instance; 
    lgfx::Bus_SPI       _bus_instance;

public:
    LGFX() {
        { // --- CONFIGURAÇÃO SPI SEGURA ---
            auto cfg = _bus_instance.config();
            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;
            // SOLUÇÃO 2: Aumentar SPI para 80MHz
            // O ESP32-S3 geralmente aguenta essa velocidade com ST7789.
            cfg.freq_write = 80000000;
            
            cfg.dma_channel = 1; // ATIVA O DMA: Essencial para performance fluida no hardware real!
            
            cfg.pin_sclk = 12; 
            cfg.pin_mosi = 11;
            cfg.pin_miso = -1; 
            cfg.pin_dc   = 13;
            
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        { // --- CONFIGURAÇÃO DO PAINEL ---
            auto cfg = _panel_instance.config();
            cfg.pin_cs       = 10;
            
            cfg.pin_rst      = -1; // Desligado no código (ligado direto no 3V3)
            cfg.pin_busy     = -1;
            
            cfg.panel_width  = 240;
            cfg.panel_height = 320;
            cfg.offset_x     = 0;
            cfg.offset_y     = 0;
            cfg.invert       = false; 
            cfg.rgb_order    = false;
            
            _panel_instance.config(cfg);
        }
        
        // Removemos o bloco de Light/Brilho, pois o fio já está no 3V3!

        setPanel(&_panel_instance);
    }
};