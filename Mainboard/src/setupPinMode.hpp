#include <Arduino.h>
#include "config.hpp"
#ifndef SETUP_PIN_MODE_HPP
#define SETUP_PIN_MODE_HPP
void setup_pin_mode(){
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    pinMode(PWM3, OUTPUT);
    pinMode(PWM4, OUTPUT);
    pinMode(L1, OUTPUT);
    pinMode(R1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(R3, OUTPUT);
    pinMode(L4, OUTPUT);
    pinMode(R4, OUTPUT);
    pinMode(ENC1A, INPUT);
    pinMode(ENC1B, INPUT);
    // pinMode(ENC2A, INPUT);
    // pinMode(ENC2B, INPUT);
    pinMode(ENC3A, INPUT);
    pinMode(ENC3B, INPUT);
    // pinMode(ENC4A, INPUT);
    // pinMode(ENC4B, INPUT);
}
#endif
