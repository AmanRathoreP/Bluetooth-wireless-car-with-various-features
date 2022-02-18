/*
Date ->          2022-02-16
Time ->          16:53:35
Day ->           Wednesday
Month Name ->    February
Unix Time ->     1645010615
File Name ->     "functions.h" when created i.e. on 2022-02-16
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Transmitter/Transmitter_code_1/functions.h" when created i.e. on 2022-02-16

This is just a header file and may you know why is this here
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Adafruit_PCD8544.h>

class Gyroscope
{
public:
    Gyroscope(short, short);
    Gyroscope(void);
    Gyroscope(bool);
    void set_offset(void);
    void set_offset(short, short);
    void get_position(int &, int &);
    void get_position(short &, short &,bool);
    private:
    void filter_values(short &, short &);
};

class Joystick
{
public:
    Joystick(short, short,short);
    Joystick(void);
    Joystick(bool);
    void get_position(short &, short &, bool &, short, short, short,bool);
    void get_position(short &, short &, bool &);
    void get_position(short &, short &);
    void get_state(bool &);void get_state(bool &,short);
    

private:
    void init(short, short,short);
    void init(void);
    void init(bool);
};

void get_motor_directions_and_speed(short &, bool &, bool &, short &, bool &, bool &, short, short, bool);
void __terminal_value__(char, bool &, bool &, bool &, bool &);
void __change_direction__(bool &, bool &, bool &, bool &);

class GUI
{
public:
GUI(GUI_info&);GUI(GUI_info&,short);GUI(short);GUI(void);
void display_data(GUI_info&);
private:
void get_home_screen(GUI_info&);
};

#endif
