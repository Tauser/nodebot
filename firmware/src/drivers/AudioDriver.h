#include <stdint.h>
#include <stddef.h>

class AudioDriver
{
public:
    bool init(int bclk, int lrck, int dout, uint32_t sampleRate);
    size_t writeBuffer(const uint8_t* data, size_t size);
    void clearBuffer(); 
    void setVolume(uint8_t level);

private:
    uint32_t _sampleRate;
    uint8_t _volume; 
};