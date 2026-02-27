#pragma once
#include <Arduino.h>
#include <Audio.h> // Agora ele sabe que é a biblioteca externa!
#include "../include/Config.h"

class AudioSys {
public:
    static bool iniciar();
    static void atualizar();
private:
    static Audio audio; // A classe da biblioteca agora será reconhecida
};