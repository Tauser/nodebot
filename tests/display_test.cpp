#include "drivers/DisplayDriver.h"
#include "core/config/hardware_config.h"

DisplayDriver display;

extern "C" void app_main()
{
    display.init();

    display.clear();
    display.drawText(10, 10, "DISPLAY OK");

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}