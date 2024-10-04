#include <Arduino.h>
#include "config.hpp"
#ifndef LINE_DETECT_HPP
#define LINE_DETECT_HPP
int line_detect(){
    // 7 line detectors and line detector 4 is the center one
    int eye1 = digitalRead(LD1);
    int eye2 = digitalRead(LD2);
    int eye3 = digitalRead(LD3);
    int eye4 = digitalRead(LD4);
    int eye5 = digitalRead(LD5);
    int eye6 = digitalRead(LD6);
    int eye7 = digitalRead(LD7);
    float error = 0;
    //error is average of detector which has line
    int count = 0;
    if(eye1 == LINE_COLOR){
        error += -3;
        count++;
    }
    if(eye2 == LINE_COLOR){
        error += -2;
        count++;
    }
    if(eye3 == LINE_COLOR){
        error += -1;
        count++;
    }
    if(eye4 == LINE_COLOR){
        error += 0;
        count++;
    }
    if(eye5 == LINE_COLOR){
        error += 1;
        count++;
    }
    if(eye6 == LINE_COLOR){
        error += 2;
        count++;
    }
    if(eye7 == LINE_COLOR){
        error += 3;
        count++;
    }
    if(count != 0){
        error /= count;
    }
    else{
        error = 0;
    }
    return error;
}
int line_follow_straight(){
    float error = line_detect();
    int linear_speed = int (Kp_straight * ((NUMBER_DETECTOR - 1)/2 - abs(error)));

    return linear_speed;
}
int line_follow_turn(){
    float error = line_detect();
    int angular_speed = int (Kp_turn * error);
    return angular_speed;
}

#endif