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
    Serial.print("Line Detector: ");
    Serial.print(eye1);
    Serial.print(eye2);
    Serial.print(eye3);
    Serial.print(eye4);
    Serial.print(eye5);
    Serial.print(eye6);
    Serial.print(eye7);
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
    if (count == 0)
        error = -10;
    // Serial.print(" .Position error of head: ");
    // Serial.println(error);
    return error;
}
int line_follow_straight(float error){
    int linear_speed = int (Kp_straight * ((NUMBER_DETECTOR - 1)/2 - abs(error)));
    linear_speed = 40;
    // Serial.print("Linear Speed: ");
    // Serial.println(linear_speed);
    return linear_speed;
}
int line_follow_turn(float error){
    // int angular_speed = int (Kp_turn * error);
    int angular_speed;
    if (error > 0)
    {
        angular_speed = 55;
    }
    else
    {
        angular_speed = -55;
    }
    // Serial.print("Angular Speed: ");
    // Serial.println(angular_speed);
    return angular_speed;
}

void turn_left(){
    Serial.println("Turn Left");
    skid_steer(vel_adjust_linear, 0);
    delay(time_adjut_linear);
    stop();
    skid_steer(0, turn_speed);
    delay(turn_time);
    stop();
}

void turn_right(){
    Serial.println("Turn Right");
    skid_steer(vel_adjust_linear, 0);
    delay(time_adjut_linear);
    stop();
    skid_steer(0, -turn_speed);
    delay(turn_time);
    stop();

}

void across_intersection(int intersection){
    Serial.print("Intersection: ");
    Serial.println(intersection);
    switch (intersection)
    {
    case 1:
        Serial.println("Intersection 1. Turn Right");
        turn_right();
        break;
    case 2:
        Serial.println("Intersection 2. Turn Left");
        turn_left();
        break;
    case 3:
        Serial.println("Intersection 3. Turn Left");
        turn_left();
        break;
    case 4:
        Serial.println("Intersection 4. Go Straight");
        break;
    case 5:
        Serial.println("Intersection 5. Turn Right");
        turn_right();
        break;
    case 6:
        Serial.println("Intersection 6. Go Straight");
        break;
    case 7:
        Serial.println("Intersection 7. Go Straight");
        break;
    case 8:
        Serial.println("Intersection 8. Turn Right");
        turn_right();
        break;
    case 9:
        Serial.println("Intersection 9. Go Straight");
        break;
    case 10:
        Serial.println("Intersection 10. Turn Right");
        turn_right();
        break;
    case 11:
        Serial.println("Intersection 11. Turn Left");
        turn_left();
        break;
    case 12:
        Serial.println("Intersection 12. STOP");
        stop();
        /*
            PUT YOUR CODE HERE
            IT WILL RUN WHEN ROBOT IS AT THE END OF THE RACE
            GOOD LUCK
        */
        break;
    default:
        break;
    }
}

void across_intersection_(int intersection){
    Serial.print("Intersection: ");
    Serial.println(intersection);
    switch (intersection)
    {
    case 1:
        Serial.println("Intersection 1. Go Straight");
        break;
    case 2:
        Serial.println("Intersection 2. Turn Right");
        turn_right();
        break;
    case 3:
        Serial.println("Intersection 3. Turn Left");
        turn_left();
        break;
    case 4:
        Serial.println("Intersection 4. STOP");
        stop();
        break;
    default:
        break;
    }
}



#endif