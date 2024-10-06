#ifndef CONFIG_HPP
#define CONFIG_HPP

// PWM pins (PWM1, PWM2, PWM3, PWM4) 4, 5, 6, 7
#define PWM1 5
#define PWM2 4
#define PWM3 6
#define PWM4 7
// Chieu quay dong co (L1, R1, L2, R2, L3, R3, L4, R4) 30, 31, 32, 33, 34, 35, 36, 37
#define L1 33
#define R1 32
#define L2 31
#define R2 30
#define L3 34
#define R3 52
#define L4 36
#define R4 53
// Encoder pins (interrupt pins) 2, 3, 18, 19, 20, 21
#define ENC1A 2
#define ENC1B 3
#define ENC2A 999
#define ENC2B 999
#define ENC3A 18
#define ENC3B 19
#define ENC4A 999
#define ENC4B 999
// Communication pins I2C (SDA, SCL), SPI (MOSI, MISO, SCK, SS)

// Line detector pins digital 38, 39, 40, 41, 42, 43, 47, 48, 49, 50
#define LINE_COLOR HIGH // 1 for black line, 0 for white line
#define NUMBER_DETECTOR 7
#define LD1 38
#define LD2 39
#define LD3 40
#define LD4 41
#define LD5 42
#define LD6 43
#define LD7 47

#define LD8 48
#define LD9 49
#define LD10 50

// Encoder information
#define pulsePerRev 330
#define gearRatio 30
#define wheelDiameter 0.065
#define encoderMax 65535
// PID parameters
#define Kp 0.5
#define Ki 0.5
#define Kd 0.5

// Kinematic
#define Kinematic_L 1

// Line following parameters
#define Kp_straight 15
#define Ki_straight 0.5
#define Kd_straight 0.5
#define Kp_turn 30
#define Ki_turn 0.5
#define Kd_turn 0.5

#endif


