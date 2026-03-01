#include "drivers/AudioDriver.h"

AudioDriver audio;

extern "C" void app_main()
{
    audio.init();
    audio.playTestTone(440); // 440Hz

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}