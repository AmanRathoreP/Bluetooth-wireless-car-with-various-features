/*
Date ->          2022-02-21
Time ->          13:33:53
Day ->           Monday
Month Name ->    February
Unix Time ->     1645430633
File Name ->     "Receiver_code_1.ino" when created i.e. on 2022-02-21
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Receiver/Receiver_code_1/Receiver_code_1.ino" when created i.e. on 2022-02-21

This is the receiver code for the project
*/

#include "constants.cpp"
#include "functions.h"

void setup()
{

    pinMode(trig_right, OUTPUT);
    pinMode(echo_right, INPUT);
    pinMode(trig_left, OUTPUT);
    pinMode(echo_left, INPUT);

    pinMode(motor_1_speed_pin, OUTPUT);
    pinMode(motor_2_speed_pin, OUTPUT);

    pinMode(motor_1_terminal_1, OUTPUT);
    pinMode(motor_1_terminal_2, OUTPUT);
    pinMode(motor_2_terminal_1, OUTPUT);
    pinMode(motor_2_terminal_2, OUTPUT);


}
void loop()
{

delay(1000);
  
    digitalWrite(motor_1_terminal_1, 1);
    digitalWrite(motor_1_terminal_2, 0);
    digitalWrite(motor_2_terminal_1, 1);
    digitalWrite(motor_2_terminal_2, 0);
    analogWrite(motor_1_speed_pin, 160);
    analogWrite(motor_2_speed_pin, 160);
delay(1000);
digitalWrite(motor_1_terminal_1, 0);
    digitalWrite(motor_1_terminal_2, 1);
    digitalWrite(motor_2_terminal_1, 0);
    digitalWrite(motor_2_terminal_2, 1);
    delay(1000);
digitalWrite(motor_1_terminal_1, 1);
    digitalWrite(motor_1_terminal_2, 0);
    digitalWrite(motor_2_terminal_1, 0);
    digitalWrite(motor_2_terminal_2, 1);
        delay(1000);
digitalWrite(motor_1_terminal_1, 0);
    digitalWrite(motor_1_terminal_2, 1);
    digitalWrite(motor_2_terminal_1, 1);
    digitalWrite(motor_2_terminal_2, 0);
    
    
  
}
