#include "AudioDriver.h"
#include <driver/i2s.h>
#include <Arduino.h>

bool AudioDriver::init(int bclk, int lrck, int dout, uint32_t sampleRate)
{
    _sampleRate = sampleRate;
    _volume = 100;

    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = _sampleRate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = bclk,
        .ws_io_num = lrck,
        .data_out_num = dout,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    if (i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL) != ESP_OK) return false;
    if (i2s_set_pin(I2S_NUM_0, &pin_config) != ESP_OK) return false;

    return true;
}

size_t AudioDriver::writeBuffer(const uint8_t* data, size_t size)
{
    size_t bytes_written = 0;
    // O portMAX_DELAY só bloqueia a Task do Áudio se o buffer DMA estiver cheio, 
    // não bloqueia o cérebro do robô.
    i2s_write(I2S_NUM_0, data, size, &bytes_written, portMAX_DELAY);
    return bytes_written;
}

void AudioDriver::clearBuffer()
{
    i2s_zero_dma_buffer(I2S_NUM_0);
}

void AudioDriver::setVolume(uint8_t level)
{
    _volume = level;
    // (A redução de volume real será feita no AudioService multiplicando os bytes, 
    // ou aqui se o DAC suportar controlo de ganho por hardware)
}