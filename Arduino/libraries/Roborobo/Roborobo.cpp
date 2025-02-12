#include "Roborobo.h"

Roborobo::Roborobo() : ultrasonic(ULTRA_SONIC), pixels(1, SERIAL_RGB, NEO_GRB + NEO_KHZ800) {
    for (int i = 4; i < 12; i++) {
        pinMode(i, OUTPUT);
    }
}

void Roborobo::move_m1_forward(byte speed) {
    digitalWrite(MOTOR_M1_DIR, HIGH);
    digitalWrite(MOTOR_M1_PWM, 255 - speed);
}

void Roborobo::move_m2_forward(byte speed) {
    digitalWrite(MOTOR_M2_DIR, HIGH);
    digitalWrite(MOTOR_M2_PWM, 255 - speed);
}

void Roborobo::move_m3_forward(byte speed) {
    digitalWrite(MOTOR_M3_DIR, HIGH);
    digitalWrite(MOTOR_M3_PWM, 255 - speed);
}

void Roborobo::move_m4_forward(byte speed) {
    digitalWrite(MOTOR_M4_DIR, LOW);
    digitalWrite(MOTOR_M4_PWM, speed);
}

void Roborobo::move_m1_backward(byte speed) {
    digitalWrite(MOTOR_M1_DIR, LOW);
    digitalWrite(MOTOR_M1_PWM, speed);
}

void Roborobo::move_m2_backward(byte speed) {
    digitalWrite(MOTOR_M2_DIR, LOW);
    digitalWrite(MOTOR_M2_PWM, speed);
}

void Roborobo::move_m3_backward(byte speed) {
    digitalWrite(MOTOR_M3_DIR, LOW);
    digitalWrite(MOTOR_M3_PWM, speed);
}

void Roborobo::move_m4_backward(byte speed) {
    digitalWrite(MOTOR_M4_DIR, HIGH);
    digitalWrite(MOTOR_M4_PWM, 255 - speed);
}

void Roborobo::move_forward(byte speed) {
    move_m1_forward(speed);
    move_m2_forward(speed);
    move_m3_forward(speed);
    move_m4_forward(speed);
}

void Roborobo::move_backward(byte speed) {
    move_m1_backward(speed);
    move_m2_backward(speed);
    move_m3_backward(speed);
    move_m4_backward(speed);
}

void Roborobo::move_left(byte speed) {
    move_m1_backward(speed);
    move_m2_forward(speed);
    move_m3_forward(speed);
    move_m4_backward(speed);
}

void Roborobo::move_right(byte speed) {
    move_m1_forward(speed);
    move_m2_backward(speed);
    move_m3_backward(speed);
    move_m4_forward(speed);
}

void Roborobo::move_left_forward(byte speed) {
    move_m1_forward(0);
    move_m2_forward(speed);
    move_m3_forward(speed);
    move_m4_forward(0);
}

void Roborobo::move_right_forward(byte speed) {
    move_m1_forward(speed);
    move_m2_forward(0);
    move_m3_forward(0);
    move_m4_forward(speed);
}

void Roborobo::move_left_backward(byte speed) {
    move_m1_backward(speed);
    move_m2_backward(0);
    move_m3_backward(0);
    move_m4_backward(speed);
}

void Roborobo::move_right_backward(byte speed) {
    move_m1_backward(0);
    move_m2_backward(speed);
    move_m3_backward(speed);
     move_m4_backward(0);
}

void Roborobo::move_left_rotate(byte speed) {
    move_m1_backward(speed);
    move_m2_forward(speed);
    move_m3_backward(speed);
    move_m4_forward(speed);
}

void Roborobo::move_right_rotate(byte speed) {
    move_m1_forward(speed);
    move_m2_backward(speed);
    move_m3_forward(speed);
    move_m4_backward(speed);
}

void Roborobo::move_stop(void) {
    move_m1_forward(0);
    move_m2_forward(0);
    move_m3_forward(0);
    move_m4_forward(0);
}