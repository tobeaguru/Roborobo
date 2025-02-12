#ifndef __ROBOROBO_H
#define __ROBOROBO_H

#include <Arduino.h>
#include "Ultrasonic.h"
#include <Adafruit_NeoPixel.h>

#define ULTRA_SONIC     2
#define SERIAL_RGB      3
#define MOTOR_M1_PWM    5
#define MOTOR_M1_DIR    4
#define MOTOR_M2_PWM    6
#define MOTOR_M2_DIR    7
#define MOTOR_M3_PWM    9
#define MOTOR_M3_DIR    8
#define MOTOR_M4_PWM    11
#define MOTOR_M4_DIR    10


class Roborobo {
public:
   Ultrasonic ultrasonic;
   Adafruit_NeoPixel pixels;

public:
    Roborobo();
    void move_forward(byte speed);
    void move_backward(byte speed);
    void move_left(byte speed);
    void move_right(byte speed);
    void move_left_forward(byte speed);
    void move_right_forward(byte speed);
    void move_left_backward(byte speed);
    void move_right_backward(byte speed);
    void move_left_rotate(byte speed);
    void move_right_rotate(byte speed);
    void move_stop();


    void move_m1_forward(byte speed);
    void move_m2_forward(byte speed);
    void move_m3_forward(byte speed);
    void move_m4_forward(byte speed);
    void move_m1_backward(byte speed);
    void move_m2_backward(byte speed);
    void move_m3_backward(byte speed);
    void move_m4_backward(byte speed);
};

#endif