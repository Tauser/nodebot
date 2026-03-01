#include "DisplayDriver.h"
#include "core/config/hardware_config.h" // A sua fonte da verdade
#include <SPI.h>

bool DisplayDriver::init() {
    _width = Hardware::Display::WIDTH;
    _height = Hardware::Display::HEIGHT;
    _blPin = Hardware::Display::PIN_BL;
    
    if (_tft) delete _tft;

    // Inicializa Hardware SPI globalmente
    SPI.begin(Hardware::Display::PIN_SCLK, -1, Hardware::Display::PIN_MOSI, Hardware::Display::PIN_CS);

    // Cria o objeto driver
    _tft = new Adafruit_ST7789(Hardware::Display::PIN_CS, Hardware::Display::PIN_DC, Hardware::Display::PIN_RST);
    
    _tft->init(_width, _height);
    _tft->setRotation(1);
    _tft->invertDisplay(false); // Ajuste conforme necessário para a sua tela
    _tft->fillScreen(0x0000);
    
    // Configura o Backlight
    if (_blPin >= 0) {
        // Compatibilidade com ESP32 Arduino Core v3.0+
        #if ESP_ARDUINO_VERSION_MAJOR >= 3
            ledcAttach(_blPin, 5000, 8);
            ledcWrite(_blPin, 255);
        #else
            ledcSetup(1, 5000, 8); 
            ledcAttachPin(_blPin, 1);
            ledcWrite(1, 255);
        #endif
    }
    
    _isInitialized = true;
    return true;
}

void DisplayDriver::setBacklight(uint8_t brightness) {
    if (_blPin >= 0) {
        #if ESP_ARDUINO_VERSION_MAJOR >= 3
            ledcWrite(_blPin, brightness);
        #else
            ledcWrite(1, brightness);
        #endif
    }
}

void DisplayDriver::clearScreen(uint16_t color) {
    if (_tft) _tft->fillScreen(color);
}

void DisplayDriver::fillRect(int x, int y, int w, int h, uint16_t color) {
    if (_tft) _tft->fillRect(x, y, w, h, color);
}

void DisplayDriver::fillRoundRect(int x, int y, int w, int h, int radius, uint16_t color) {
    if (_tft) _tft->fillRoundRect(x, y, w, h, radius, color);
}

void DisplayDriver::fillCircle(int x, int y, int r, uint16_t color) {
    if (_tft) _tft->fillCircle(x, y, r, color);
}

void DisplayDriver::pushImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if (_tft) _tft->drawRGBBitmap(x, y, data, w, h);
}