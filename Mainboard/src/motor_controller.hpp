#include <Arduino.h>
#include "config.hpp"
#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

void motor_control(int motor, int speed){
    Serial.print("Motor ");
    Serial.print(motor);
    Serial.print(" Speed: ");
    Serial.println(speed);
    switch (motor)
    {
    case 1:
        if(speed >= 0){
            digitalWrite(L1, HIGH);
            digitalWrite(R1, LOW);
            analogWrite(PWM1, speed);
        }
        else{
            digitalWrite(L1, LOW);
            digitalWrite(R1, HIGH);
            analogWrite(PWM1, -speed);
        }
        break;
    case 2:
        if(speed >= 0){
            digitalWrite(L2, HIGH);
            digitalWrite(R2, LOW);
            analogWrite(PWM2, speed);
        }
        else{
            digitalWrite(L2, LOW);
            digitalWrite(R2, HIGH);
            analogWrite(PWM2, -speed);
        }
        break;
    case 3:
        if(speed >= 0){
            digitalWrite(L3, HIGH);
            digitalWrite(R3, LOW);
            analogWrite(PWM3, speed);
        }
        else{
            digitalWrite(L3, LOW);
            digitalWrite(R3, HIGH);
            analogWrite(PWM3, -speed);
        }
        break;
    case 4:
        if(speed >= 0){
            digitalWrite(L4, HIGH);
            digitalWrite(R4, LOW);
            analogWrite(PWM4, speed);
        }
        else{
            digitalWrite(L4, LOW);
            digitalWrite(R4, HIGH);
            analogWrite(PWM4, -speed);
        }
        break;
    
    }
}

void straight(int speed){
    Serial.print("Straight: ");
    Serial.println(speed);
    motor_control(1, speed);
    motor_control(2, speed);
    motor_control(3, speed);
    motor_control(4, speed);
}

void turn(int speed){
    Serial.print("Turn: ");
    Serial.println(speed);
    motor_control(1, speed);
    motor_control(2, speed);
    motor_control(3, -speed);
    motor_control(4, -speed);
}

void skid_steer(int speed, int angular_speed){
    Serial.print("Skid Steer: ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.println(angular_speed);
    motor_control(1, speed + angular_speed);
    motor_control(2, speed + angular_speed);
    motor_control(3, speed - angular_speed);
    motor_control(4, speed - angular_speed);
}

void stop(){
    motor_control(1, 0);
    motor_control(2, 0);
    motor_control(3, 0);
    motor_control(4, 0);
}

#endif