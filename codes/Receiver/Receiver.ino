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

motor motor_info;
bool state = 0; //* when 0 motor will not work
void setup()
{
    Blutooth();

    pinMode(trig_right, OUTPUT);
    pinMode(echo_right, INPUT);
    pinMode(trig_left, OUTPUT);
    pinMode(echo_left, INPUT);

    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);

    pinMode(motor_1_terminal_1, OUTPUT);
    pinMode(motor_1_terminal_2, OUTPUT);
    pinMode(motor_2_terminal_1, OUTPUT);
    pinMode(motor_2_terminal_2, OUTPUT);

    pinMode(state_pin, OUTPUT);

    // Serial.begin(4800);
}
void loop()
{
    Blutooth().read(motor_info, state);
    if (state)
    {
        motor_controller(motor_info);
    }
    digitalWrite(state_pin, state);
}
