#include <Arduino.h>
#include "config.hpp"
#include "setupPinMode.hpp"
#include "motor_controller.hpp"
#include "line_detect.hpp"

volatile int encoder1 = 0;
volatile int encoder2 = 0;
volatile int encoder3 = 0;
volatile int encoder4 = 0;

volatile float x = 0;
volatile float y = 0;
volatile float theta = 0;

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

void setup() {
  Serial.begin(9600);
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
  Serial.println("Setup done!");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true)
  {
    int straight_speed = line_follow_straight();
    int turn_speed = line_follow_turn();
    skid_steer(straight_speed, turn_speed);

  }
  
}