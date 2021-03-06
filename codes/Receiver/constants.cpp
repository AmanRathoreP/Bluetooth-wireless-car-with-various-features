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

#define motor_1_speed_pin 9
#define motor_2_speed_pin 10
#define motor_1_terminal_1_pin 2
#define motor_1_terminal_2_pin 3
#define motor_2_terminal_1_pin 4
#define motor_2_terminal_2_pin 5

#define state_pin 12

struct motor
{
    short motor_1_speed = 0;
    bool motor_1_terminal_1 = 0;
    bool motor_1_terminal_2 = 0;
    short motor_2_speed = 0;
    bool motor_2_terminal_1 = 0;
    bool motor_2_terminal_2 = 0;
};
