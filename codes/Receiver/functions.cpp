/*
Date ->          2022-02-21
Time ->          13:39:18
Day ->           Monday
Month Name ->    February
Unix Time ->     1645430958
File Name ->     "functions.cpp" when created i.e. on 2022-02-21
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Receiver/Receiver_code_1/functions.cpp" when created i.e. on 2022-02-21

This file contains some functions and may some class for the proper functioning on the Receiver
*/

#include "constants.cpp"
#include <Arduino.h>
#include "functions.h"

void motor_controller(motor motor_data)
{

    /*
        struct motor
        {
            short motor_1_speed = 0;
            bool motor_1_terminal_1 = 0;
            bool motor_1_terminal_2 = 0;
            short motor_2_speed = 0;
            bool motor_2_terminal_1 = 0;
            bool motor_2_terminal_2 = 0;
        };
    */

    //  motor_data.motor_1_speed = map(motor_data.motor_1_speed, 0, 1024, 0, 255);
    //  motor_data.motor_2_speed = map(motor_data.motor_2_speed, 0, 1024, 0, 255);

    digitalWrite(motor_1_terminal_1, motor_data.motor_1_terminal_1);
    digitalWrite(motor_1_terminal_2, motor_data.motor_1_terminal_2);
    digitalWrite(motor_2_terminal_1, motor_data.motor_2_terminal_1);
    digitalWrite(motor_2_terminal_2, motor_data.motor_2_terminal_2);
    analogWrite(motor_1_speed_pin, motor_data.motor_1_speed);
    analogWrite(motor_2_speed_pin, motor_data.motor_2_speed);
}

Blutooth::Blutooth(int baud_rate)
{
    init(baud_rate);
}
Blutooth::Blutooth()
{
    init(9600);
}
void Blutooth::init(int baud_rate)
{
    static bool called = false;
    if (!called)
    {
        Serial.begin(baud_rate);
        called = true;
    }
}

void Blutooth::__read(String &data)
{
    if (Serial.available() )
    {
        data = Serial.readStringUntil('t').substring(0,13);
    }
}
void Blutooth::__write(String data)
{
    int S_len = data.length();
    char data_array[S_len + 1];
    strcpy(data_array, data.c_str());
    Serial.write(data_array);
}
void Blutooth::motor_encode(motor data_struct, String &data_string, bool state)
{
    /*
    struct data_struct
    {
        bool motor_1_terminal_1 = 0;
        bool motor_1_terminal_2 = 0;
        short motor_1_speed = 0;
        bool motor_2_terminal_1 = 0;
        bool motor_2_terminal_2 = 0;
        short motor_2_speed = 0;
    };
    */

    String motor_1_speed = String(data_struct.motor_1_speed);
    String motor_2_speed = String(data_struct.motor_2_speed);

    if (data_struct.motor_1_speed <= 9)
    {
        motor_1_speed = "000" + motor_1_speed;
    }
    else if (data_struct.motor_1_speed <= 99)
    {
        motor_1_speed = "00" + motor_1_speed;
    }
    else if (data_struct.motor_1_speed <= 999)
    {
        motor_1_speed = "0" + motor_1_speed;
    }

    if (data_struct.motor_2_speed <= 9)
    {
        motor_2_speed = "000" + motor_2_speed;
    }
    else if (data_struct.motor_2_speed <= 99)
    {
        motor_2_speed = "00" + motor_2_speed;
    }
    else if (data_struct.motor_2_speed <= 999)
    {
        motor_2_speed = "0" + motor_2_speed;
    }

    data_string = String(data_struct.motor_1_terminal_1) + String(data_struct.motor_1_terminal_2) + String(motor_1_speed) + String(data_struct.motor_2_terminal_1) + String(data_struct.motor_2_terminal_2) + String(motor_2_speed) + String(state);
}

void Blutooth::motor_decode(String data_string, motor &data_struct, bool &state)
{
    /*
    struct data_struct
    {
        bool motor_1_terminal_1 = 0;
        bool motor_1_terminal_2 = 0;
        short motor_1_speed = 0;
        bool motor_2_terminal_1 = 0;
        bool motor_2_terminal_2 = 0;
        short motor_2_speed = 0;
    };
    */
    //  data_string = data_string.substring(2,7);
    //   data_string = data_string.charAt(5);

    data_struct.motor_1_terminal_1 = bool_or_not(String(data_string.charAt(0)));
    data_struct.motor_1_terminal_2 = bool_or_not(String(data_string.charAt(1)));
    data_struct.motor_1_speed = (short)String(data_string.substring(2, 6)).toInt();
    data_struct.motor_2_terminal_1 = bool_or_not(String(data_string.charAt(6)));
    data_struct.motor_2_terminal_2 = bool_or_not(String(data_string.charAt(7)));
    data_struct.motor_2_speed = (short)String(data_string.substring(8, 12)).toInt();
    state = bool_or_not(String(data_string.charAt(12)));
}

bool Blutooth::bool_or_not(String str)
{
    if (str == "0")
    {
        return 0;
    }
    return 1;
}
void Blutooth::read(motor &data, bool &state)
{
    String data_str;
    __read(data_str);
    motor_decode(data_str, data, state);
}
void Blutooth::write(motor data, bool state)
{
    String data_str;
    motor_encode(data, data_str, state);
    __write(data_str);
}
