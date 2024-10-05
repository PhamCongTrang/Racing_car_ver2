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
    eye5 = 0;
    int eye6 = digitalRead(LD6);
    eye6 = 0;
    int eye7 = digitalRead(LD7);
    Serial.print("Line Detector: ");
    Serial.print(eye1);
    Serial.print(eye2);
    Serial.print(eye3);
    Serial.print(eye4);
    Serial.print(eye5);
    Serial.print(eye6);
    Serial.println(eye7);
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

    if (count  > 2)
        error = 10; // if more than 2 detectors detect line, it means the robot is at the intersection
    Serial.print("Error: ");
    Serial.println(error);
    return error;
}
int line_follow_straight(float error){
    int linear_speed = int (Kp_straight * ((NUMBER_DETECTOR - 1)/2 - abs(error)));
    linear_speed = 40;
    Serial.print("Linear Speed: ");
    Serial.println(linear_speed);
    return linear_speed;
}
int line_follow_turn(float error){
    // int angular_speed = int (Kp_turn * error);
    int angular_speed;
    if (error > 0)
    {
        angular_speed = 80;
    }
    else
    {
        angular_speed = -80;
    }
    Serial.print("Angular Speed: ");
    Serial.println(angular_speed);
    return angular_speed;
}

void turn_left(){
    Serial.println("Turn Left");
    for (int i = 0; i < 20; i++)
    {
        skid_steer(0, 80);
    }
    // while (line_detect() <= 0)
    // {
    //     skid_steer(0, 30);
    // }
}

void turn_right(){
    Serial.println("Turn Right");
    for (int i = 0; i < 10; i++)
    {
        skid_steer(0, -80);
    }
    // while (line_detect() >= 0)
    // {
    //     skid_steer(0, -30);
    // }
}

void across_intersection(int intersection){
    Serial.print("Intersection: ");
    Serial.println(intersection);
    turn_right();
    switch (-1)
    {
    case 1:
        turn_right();
        break;
    case 2:
        turn_left();
        break;
    case 3:
        turn_left();
        break;
    case 4:
        break;
    case 5:
        turn_right();
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        turn_right();
        break;
    case 9:
        break;
    case 10:
        turn_right();
        break;
    case 11:
        turn_left();
        break;
    case 12:
        break;
    default:
        break;
    }
}


#endif