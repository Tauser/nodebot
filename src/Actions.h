#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class Actions {
public:
    static void dizerSim();
    static void dizerNao();
    static void olharCurioso();
    static void reagirACarinho();
    static void reagirASusto();
    static void centralizarSuave();
};