/*
Date ->          2022-02-16
Time ->          15:16:43
Day ->           Wednesday
Month Name ->    February
Unix Time ->     1645004803
File Name ->     "functions_etc.cpp" when created i.e. on 2022-02-16
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Transmitter/Transmitter_code_1/functions_etc.cpp" when created i.e. on 2022-02-16

This file contains some functions and may some class for the proper functioning on the Transmitter
*/

#include <Wire.h>
#include "constants.cpp"
#include <Arduino.h>
#include "functions.h"



Gyroscope::Gyroscope(short x_offset, short y_offset)
{
    set_offset(x_offset, y_offset);
}
Gyroscope::Gyroscope(void)
{
    set_offset();
}
Gyroscope::Gyroscope(bool set_or_not)
{
    if (set_or_not)
        set_offset();
}

void Gyroscope::get_position(int &x, int &y)
{
       get_position(x, y);
}
void Gyroscope::get_position(short &x, short &y, bool filter)
{

    Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 4, 1); // Note: I'm not using z value as my work can be done fine useing x and y values

    x = (Wire.read() | Wire.read() << 8); // X-axis value
    y = (Wire.read() | Wire.read() << 8); // Y-axis value

    if (filter)
        filter_values(x, y);
}

void Gyroscope::filter_values(short &x, short &y){
  if (x < (-260) )
       {
           x = -259;
        }
        if (y  < (-364))
        {
            y =  -363;
        }
 

 if (x > 269 )
       {
           x = 268;
        }
        if (y  >166)
        {
            y =  165;
        }

        x = map(x, -260, 269, -511, 511);
        y = map(y, -365, 166, -511, 511); //  y=map(y, -260, 269, 0, 1023);  // y=map(y, -310, 233, 0, 1024);

        if (((7) > x) && (x > (-17)))
            x = 0;
        if (((1) > y) && (y > (-24)))
            y = 0;

        if (y <= (-507))
            y = (-511);
        else if ((y > 425) && (y <= 431))
            y = 430;

        x *= (-1); // to make things work in an systematic manner
        y *= (-1); // to make things work in an systematic manner
  }
  

void Gyroscope::set_offset(short x_offset, short y_offset)
{

    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D);                // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    Wire.endTransmission();
    delay(10);

    // x_axis offset calibration
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1E);     // X-axis offset register
    Wire.write(x_offset); // round(difference_of(256, incorrent value)/4)
    Wire.endTransmission();
    delay(10);
    // y_axis offset calibration
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1F);     // Y-axis offset register
    Wire.write(y_offset); // round(difference_of(256, incorrent value)/4)
    Wire.endTransmission();
    delay(10);
}
void Gyroscope::set_offset(void)
{
    set_offset(0, -11);
}

//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope
//! Note: Below given is the class of Joystick but not of Gyroscope

Joystick::Joystick(short x, short y,short state_pin)
{
    init(x, y,state_pin);
}
Joystick::Joystick(void)
{
    init(A0, A1,7);
}
Joystick::Joystick(bool set_or_not)
{
    init(set_or_not);
}

void Joystick::get_position(short &x, short &y, bool &_state, short pin_x, short pin_y, short state_pin, bool filter)
{
    x = analogRead(pin_x);
    y = analogRead(pin_y);


get_state(_state,state_pin);
    if (filter)
    {
        x = map(x, 0, 1023, -511, 511);
        y = map(y, 0, 1023, -511, 511);

        if ((x > (-8)) && (x < (-4)))
        {
            x = 0;
        }
        if ((y > (-14)) && (y < (-8)))
        {
            y = 0;
        }
    }
}
void Joystick::get_position(short &x, short &y, bool &_state)
{
    get_position(x, y, _state, A0, A1, 7, 1);
}
void Joystick::get_position(short &x, short &y)
{ bool fake_state=0;
    get_position(x, y, fake_state, A0, A1, 7, 1);
}
void Joystick::get_state( bool &_state,short state_pin)
{
       if  (!(digitalRead(state_pin)))
    {_state = !_state;}delay(100);
}void Joystick::get_state( bool &_state)
{
       get_state(_state,7);
}
void Joystick::init(void)
{
    init(A0, A1,7);
}
void Joystick::init(short x_pin, short y_pin,short state_pin)
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
    pinMode(state_pin, INPUT_PULLUP);
}
void Joystick::init(bool set_or_not)
{
    if (set_or_not)
        init();
}

//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things
//! Note: This is the end of the class Joystick but not of other things

void get_motor_directions_and_speed(short &motor_1_speed, bool &motor_1_terminal_1, bool &motor_1_terminal_2, short &motor_2_speed, bool &motor_2_terminal_1, bool &motor_2_terminal_2, short x_coordinate, short y_coordinate, bool state)
{

    if ((x_coordinate == 0) && (y_coordinate == 0))
    {
        motor_1_speed = 0;
        motor_2_speed = 0;
        motor_1_terminal_1 = 0;
        motor_1_terminal_2 = 0;
        motor_2_terminal_1 = 0;
        motor_2_terminal_2 = 0;
    }
    else if (x_coordinate == 0)
    {
        //* Go forward/backward without turning

        if (y_coordinate > 0)
        { //* Go forward
            motor_1_speed = y_coordinate * 2;
            __terminal_value__('f', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
        }
        else
        { //* Go backward
            motor_1_speed = y_coordinate * (-1) * 2;
            __terminal_value__('b', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
        }
    }
    else if (y_coordinate > 0)
    {
        //* Going forward+turning
        if (x_coordinate < 0)
        { //* Going forward+left turn
            __terminal_value__('l', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = y_coordinate + (x_coordinate * (-1));
        }
        else if (x_coordinate > 0)
        { //* Going forward+right turn
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = y_coordinate + x_coordinate;
        }
    }
    else if (y_coordinate < 0)
    {
        //* Going backword+turning
        if (x_coordinate < 0)
        { //* Going backword+left turn
            __terminal_value__('l', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = (y_coordinate + x_coordinate) * (-1);
        }
        else if (x_coordinate > 0)
        { //* Going backword+right turn
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = (y_coordinate * (-1)) + x_coordinate;
        }
    }
    if (y_coordinate == 0)
    {
        //* just turning without moving forward or backwards
        if (x_coordinate < 0)
        {
            //* Turn Left
            __terminal_value__('l', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = (x_coordinate * (-1)) / turning_speed_divide_constant;
        }
        else if (x_coordinate > 0)
        {
            //* Turn Right
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = x_coordinate / turning_speed_divide_constant;
        }
    }

    motor_2_speed = motor_1_speed;
}
void __terminal_value__(char direction_to_turn, bool &motor_1_terminal_1, bool &motor_1_terminal_2, bool &motor_2_terminal_1, bool &motor_2_terminal_2)
{
    switch (direction_to_turn)
    {
    case 'r': //* for Right
        motor_1_terminal_1 = 1;
        motor_1_terminal_2 = 0;
        motor_2_terminal_1 = 0;
        motor_2_terminal_2 = 1;
        break;
    case 'l': //* for Left
        motor_1_terminal_1 = 0;
        motor_1_terminal_2 = 1;
        motor_2_terminal_1 = 1;
        motor_2_terminal_2 = 0;
        break;
    case 'f': //* for Forward
        motor_1_terminal_1 = 0;
        motor_1_terminal_2 = 1;
        motor_2_terminal_1 = 0;
        motor_2_terminal_2 = 1;
        break;
    case 'b': //* for Backword
        motor_1_terminal_1 = 1;
        motor_1_terminal_2 = 0;
        motor_2_terminal_1 = 1;
        motor_2_terminal_2 = 0;
        break;
        // case 'R': //* for Right
        //     motor_1_terminal_1 = 1;
        //     motor_1_terminal_2 = 0;
        //     motor_2_terminal_1 = 0;
        //     motor_2_terminal_2 = 1;
        //     break;
        // case 'L': //* for Left
        //     motor_1_terminal_1 = 0;
        //     motor_1_terminal_2 = 1;
        //     motor_2_terminal_1 = 1;
        //     motor_2_terminal_2 = 0;
        //     break;
        // case 'F': //* for Forward
        //     motor_1_terminal_1 = 0;
        //     motor_1_terminal_2 = 1;
        //     motor_2_terminal_1 = 0;
        //     motor_2_terminal_2 = 1;
        //     break;
        // case 'B': //* for Backword
        //     motor_1_terminal_1 = 1;
        //     motor_1_terminal_2 = 0;
        //     motor_2_terminal_1 = 1;
        //     motor_2_terminal_2 = 0;
        //     break;

    default:
        break;
    }
}

void __change_direction__(bool &motor_1_terminal_1, bool &motor_1_terminal_2, bool &motor_2_terminal_1, bool &motor_2_terminal_2)
{
    motor_1_terminal_1 = !motor_1_terminal_1;
    motor_1_terminal_2 = !motor_1_terminal_2;
    motor_2_terminal_1 = !motor_2_terminal_1;
    motor_2_terminal_2 = !motor_2_terminal_2;
}
