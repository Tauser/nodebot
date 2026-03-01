#include "drivers/ServoDriver.h"
#include "core/config/hardware_config.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

ServoDriver servo;

extern "C" void app_main()
{
    servo.init();

    while (true)
    {
        servo.setAngle(Hardware::Servo::PIN_HEAD, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        servo.setAngle(Hardware::Servo::PIN_HEAD, 90);
        vTaskDelay(pdMS_TO_TICKS(1000));

        servo.setAngle(Hardware::Servo::PIN_HEAD, 180);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}