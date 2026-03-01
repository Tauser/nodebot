#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

class DisplayDriver {
public:
    DisplayDriver() = default;
    ~DisplayDriver() = default;

    // Inicializa o hardware de vídeo
    bool init();
    
    // Controlo de ecrã
    void clearScreen(uint16_t color = 0x0000);
    void setBacklight(uint8_t brightness);
    
    // Primitivas Gráficas (Essenciais para desenhar emoções proceduralmente)
    void fillRect(int x, int y, int w, int h, uint16_t color);
    void fillRoundRect(int x, int y, int w, int h, int radius, uint16_t color);
    void fillCircle(int x, int y, int r, uint16_t color);
    
    // Para texturas complexas (Sprites RGB565)
    void pushImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);

private:
    uint16_t _width;
    uint16_t _height;
    int _blPin;
    bool _isInitialized = false;
    
    // Ponteiro para o driver Adafruit
    Adafruit_ST7789* _tft = nullptr;
};