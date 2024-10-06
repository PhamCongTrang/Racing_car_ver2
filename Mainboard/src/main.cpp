#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"
#include "setupPinMode.hpp"
#include "motor_controller.hpp"
#include "line_detect.hpp"

volatile int encoder1 = 0;
volatile int encoder2 = 0;
volatile int encoder3 = 0;
volatile int encoder4 = 0;

volatile float error = 0;

volatile float x = 0;
volatile float y = 0;
volatile float theta = 0;

volatile int intersection = -1;

String signal_control = "";

void encoder_update_1(){
  if(digitalRead(ENC1A) == digitalRead(ENC1B)){
    encoder1++;
  }else{
    encoder1--;
  }
  // Skid Steer
  encoder2 = encoder1;

}
void encoder_update_2(){
  if(digitalRead(ENC2A) == digitalRead(ENC2B)){
    encoder2++;
  }else{
    encoder2--;
  }
}
void encoder_update_3(){
  if(digitalRead(ENC3A) == digitalRead(ENC3B)){
    encoder3++;
  }else{
    encoder3--;
  }
  // Skid Steer
  encoder4 = encoder3;
}
void encoder_update_4(){
  if(digitalRead(ENC4A) == digitalRead(ENC4B)){
    encoder4++;
  }else{
    encoder4--;
  }
}

void update_position(){
  float delta_right = (encoder1 + encoder2)/2 *PI * wheelDiameter / pulsePerRev;
  float delta_left = (encoder3 + encoder4)/2 *PI * wheelDiameter / pulsePerRev;
  float delta_theta = (delta_right - delta_left) / wheelDiameter;
  float delta_s = (delta_right + delta_left) / 2;
  x += delta_s * cos(theta + delta_theta/2);
  y += delta_s * sin(theta + delta_theta/2);
  theta += delta_theta;
  if (theta > PI){
    theta -= 2*PI;
  }else if(theta < -PI){
    theta += 2*PI;
  }
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
String payload = "";
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    payload += c;        
  }
  // check if payload in "A" "B" "C" "D" "E" "R" then assign to signal_control
  if (payload == "A" || payload == "B" || payload == "C" || payload == "D" || payload == "E" || payload == "R"){
    signal_control = payload;
  }
}
// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write(signal_control.c_str());  /*send string on request */
  Wire.write("\n");
  // convert intersection to string and send
  Wire.write(String(intersection).c_str());
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  setup_pin_mode();
  attachInterrupt(digitalPinToInterrupt(ENC1A), encoder_update_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1B), encoder_update_1, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(ENC2A), encoder_update_2, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(ENC2B), encoder_update_2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC3A), encoder_update_3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC3B), encoder_update_3, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(ENC4A), encoder_update_4, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(ENC4B), encoder_update_4, CHANGE);
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */

  Serial.println("Setup done!");
}

void pause_check(int intersection_){
    while(intersection_ == 0 && signal_control != "A"){
        Serial.println("Robot in Start Point. Waiting for signal A...");
        skid_steer(0, 0);
    }
    while (intersection_ == 3 && signal_control != "C") {
        Serial.println("Robot in A Point. Waiting for signal C...");
        skid_steer(0, 0);
    }

    while (intersection_ == 6 && signal_control != "D") {
        Serial.println("Robot in C Point. Waiting for signal D...");
        skid_steer(0, 0);
    }

    while (intersection_ == 9 && signal_control != "E") {
        Serial.println("Robot in D Point. Waiting for signal E...");
        skid_steer(0, 0);
    }

    while (intersection_ == 12 && signal_control != "R") {
        Serial.println("STOP. Race is Ended. Congratulation!");
        skid_steer(0, 0);
    }

    Serial.println("Resume. Robot is moving...");
}

void pause_check_(int intersection_){
    while(intersection_ == 0 && signal_control != "A"){
        Serial.print("Signal Control:");
        Serial.print(signal_control);
        Serial.print(". Intersection:");
        Serial.print(intersection_);
        Serial.println(". Robot in Start Point. Waiting for signal A...");
        skid_steer(0, 0);
    }
    while (intersection_ == 1 && signal_control != "C") {
        Serial.print("Signal Control:");
        Serial.print(signal_control);
        Serial.print(". Intersection:");
        Serial.print(intersection_);
        Serial.println(" .Robot in A Point. Waiting for signal C...");
        skid_steer(0, 0);
    }

    while (intersection_ == 2 && signal_control != "D") {
        Serial.print("Signal Control:");
        Serial.print(signal_control);
        Serial.print(". Intersection:");
        Serial.print(intersection_);
        Serial.println(". Robot in C Point. Waiting for signal D...");
        skid_steer(0, 0);
    }

  }

void loop() {
  // put your main code here, to run repeatedly:
  if (error == 10) 
    error = 0;

  float temp = line_detect();
  if (temp != -10){
    error = temp;
  }

  Serial.print(". Position error of head: ");
  Serial.println(error);

  if (error == 10)
  {
    intersection += 1;
    if (intersection == 4)
    {
      stop();
      while (1)
      {
        skid_steer(0, 0);
      }
    }
    pause_check_(intersection);
    stop();
    across_intersection_(intersection);
  } 
  // else if (abs(error) < 1) { // Permit error smaller than 1
  //   int straight_speed = line_follow_straight(error);
  //   skid_steer(straight_speed, 0);
  // } 
  // else {
  //   int turn_speed = line_follow_turn(error);
  //   skid_steer(10, turn_speed);
  // }
  else {
    skid_steer(50, 5*error);
  }
  
}
