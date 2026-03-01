#include "drivers/CameraDriver.h"

CameraDriver camera;

extern "C" void app_main()
{
    camera.init();

    while (true)
    {
        auto frame = camera.capture();

        if (frame != nullptr)
        {
            printf("Frame capturado\n");
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}