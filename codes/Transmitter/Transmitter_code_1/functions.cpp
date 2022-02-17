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

// class functions::Gyroscope(){}
// ;

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

void Gyroscope::get_position(float &x, float &y)
{
    Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 4, 1); // Note: I'm not using z value as my work can be done fine useing x and y values

    x = (Wire.read() | Wire.read() << 8); // X-axis value
                                          //  X_out = X_out / 256;                      // For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
    y = (Wire.read() | Wire.read() << 8); // Y-axis value
                                          //  Y_out = Y_out / 256;                      // For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
}

void Gyroscope::get_position(int &x, int &y)
{
    float x_axis_value = x;
    float y_axis_value = y;
    get_position(x_axis_value, y_axis_value);
    x = (int)x_axis_value;
    y = (int)y_axis_value;
}
void Gyroscope::get_position(short &x, short &y)
{
    float x_axis_value = x;
    float y_axis_value = y;
    get_position(x_axis_value, y_axis_value);
    x = (short)x_axis_value;
    y = (short)y_axis_value;
}

void Gyroscope::set_offset(short x_offset, short y_offset)
{

    Wire.beginTransmission(ADXL345); // Start communicating with the device
    Wire.write(0x2D);                // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    Wire.endTransmission();
    delay(10);
    

/*
    Wire.beginTransmission(ADXL345); 
    Wire.write(0x31);        
    Wire.write(15); // dec(15) = 0000 1111 in binary
    Wire.endTransmission();
    delay(10);
*/

    // This code goes in the SETUP section
    // Off-set Calibration
    // X-axis
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1E);     // X-axis offset register
    Wire.write(x_offset); // round(difference_of(256, incorrent value)/4)
    Wire.endTransmission();
    delay(10);
    // Y-axis
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

// void Joystick::get_position(int &x, int &y, short pin_x, short pin_y)
// {
//     volatile short x_val=x,y_val=y;
//     get_position(x_val, y_val, (short)pin_x, (short)pin_y);
//     x = (int)x;
//     y = (int)y;
// }
void Joystick::get_position(short &x, short &y, bool &_state, short pin_x, short pin_y, short state_pin, bool filter)
{
    x = analogRead(pin_x);
    y = analogRead(pin_y);


get_state(_state,state_pin);
    if (filter)
    {
        if ((x > 500) && (x < 515))
        {
            x = 511;
        }
        if ((y > 495) && (y < 515))
        {
            y = 511;
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
    {_state = !_state;}delay(200);
}void Joystick::get_state( bool &_state)
{
       get_state(_state,7);
}
// void Joystick::get_position(int &x, int &y)
// {
//   volatile short x_val=x,y_val=y;
//     get_position(x_val, y_val, A0, A1);
//     x = (int)x;
//     y = (int)y;
// }

// void Joystick::set_offset(short x_offset, short y_offset)
// {

// Wire.beginTransmission(ADXL345); // Start communicating with the device
// Wire.write(0x2D);                // Access/ talk to POWER_CTL Register - 0x2D
// // Enable measurement
// Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
// Wire.endTransmission();
// delay(10);

// /*
//     Wire.beginTransmission(ADXL345);
//     Wire.write(0x31);
//     Wire.write(15); // dec(15) = 0000 1111 in binary
//     Wire.endTransmission();
//     delay(10);
// */

// // This code goes in the SETUP section
// // Off-set Calibration
// // X-axis
// Wire.beginTransmission(ADXL345);
// Wire.write(0x1E);     // X-axis offset register
// Wire.write(x_offset); // round(difference_of(256, incorrent value)/4)
// Wire.endTransmission();
// delay(10);
// // Y-axis
// Wire.beginTransmission(ADXL345);
// Wire.write(0x1F);     // Y-axis offset register
// Wire.write(y_offset); // round(difference_of(256, incorrent value)/4)
// Wire.endTransmission();
// delay(10);
// }
// void Joystick::set_offset(void)
// {
//     set_offset(0, -11);
// }
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
