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
String datas;
void setup()
{
    Blutooth(); //* init of "Blutooth" class

    pinMode(motor_1_speed_pin, OUTPUT);
    pinMode(motor_2_speed_pin, OUTPUT);

    pinMode(motor_1_terminal_1_pin, OUTPUT);
    pinMode(motor_1_terminal_2_pin, OUTPUT);
    pinMode(motor_2_terminal_1_pin, OUTPUT);
    pinMode(motor_2_terminal_2_pin, OUTPUT);

    pinMode(state_pin, OUTPUT);

}
void loop()
{
//    Blutooth().read(motor_info, state);



Blutooth().__read(datas);
Blutooth().motor_decode(datas,motor_info,state);

//if(state==1){digitalWrite(state_pin, HIGH);}else{digitalWrite(state_pin, LOW);}
digitalWrite(state_pin, state);



        motor_controller(motor_info);
//    String text_to_display = String("R = " + String(motor_info.motor_1_terminal_1) + ", " + String(motor_info.motor_1_terminal_2) + ", " + String(motor_info.motor_1_speed) + "\nL = " + String(motor_info.motor_2_terminal_1) + ", " + String(motor_info.motor_2_terminal_2) + ", " + String(motor_info.motor_2_speed));
//    Serial.println(text_to_display);

  
}
