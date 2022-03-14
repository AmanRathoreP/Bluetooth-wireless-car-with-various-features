/*
Date ->          2022-02-21
Time ->          13:37:19
Day ->           Monday
Month Name ->    February
Unix Time ->     1645430839
File Name ->     "constants.cpp" when created i.e. on 2022-02-21
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Receiver/Receiver_code_1/constants.cpp" when created i.e. on 2022-02-21

This is the constants file of the receiver
*/

const short int trig_right = 8;
const short int echo_right = 9;
const short int trig_left = 6;
const short int echo_left = 7;
// const short int motor_1_speed_pin = A0;
// const short int motor_2_speed_pin = A1;
const short int motor_1_terminal_1 = 2;
const short int motor_1_terminal_2 = 3;
const short int motor_2_terminal_1 = 4;
const short int motor_2_terminal_2 = 5;

const short int state_pin = 12;

struct motor
{
    short motor_1_speed = 0;
    bool motor_1_terminal_1 = 0;
    bool motor_1_terminal_2 = 0;
    short motor_2_speed = 0;
    bool motor_2_terminal_1 = 0;
    bool motor_2_terminal_2 = 0;
};