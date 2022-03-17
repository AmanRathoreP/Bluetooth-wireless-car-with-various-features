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
//#include "constants.cpp"

class Gyroscope
{
public:
    Gyroscope(short, short);
    Gyroscope(void);
    Gyroscope(bool);
    void set_offset(void);
    void set_offset(short, short);
    void get_position(int &, int &);
    void get_position(short &, short &, bool);

private:
    void filter_values(short &, short &);
};

class Joystick
{
public:
    Joystick(short, short, short);
    Joystick(void);
    Joystick(bool);
    void get_position(short &, short &, bool &, short, short, short, bool);
    void get_position(short &, short &, bool &);
    void get_position(short &, short &);
    void get_state(bool &);
    void get_state(bool &, short);

private:
    void init(short, short, short);
    void init(void);
    void init(bool);
};

void get_motor_directions_and_speed(short &, bool &, bool &, short &, bool &, bool &, short, short, bool);
void __terminal_value__(char, bool &, bool &, bool &, bool &);
void __change_direction__(bool &, bool &, bool &, bool &);

class GUI
{
public:
    GUI(GUI_info &);
    GUI(GUI_info &, short);
    GUI(short);
    GUI(void);
    void display_data(GUI_info &, motor &);
    void set_score(long);
    void reset_score(void);
    void menu_lock(Adafruit_PCD8544);

private:
    void get_home_screen(GUI_info &);
    void DeveloperMode(GUI_info &, motor &);
    void FreePlay(GUI_info &, motor &);
    void LineBalancing(GUI_info &, motor &);
    void SpeedPlay(GUI_info &, motor &);
    void AvoidObstacle(GUI_info &);
    void Setings(GUI_info &);
    void draw_stuff(GUI_info &, String);
    void get_previous_score(long &);
    void store_long_in_eeprom(short, long);
    void get_long_from_eeprom(short, long &);
    void store_score(long);
    void get_distance_away_from(int &, int &);
};

class InterfaceSensor
{
    void init_ultra_sonic();

public:
    void get_distance(int &, int &);
};

class Blutooth
{
public:
    Blutooth(int);
    Blutooth();
    void read(motor &, bool &);
    void write(motor, bool);

private:
    void init(int);
    void __read(String &);
    void __write(String);
    void motor_encode(motor, String &, bool);
    void motor_decode(String, motor &, bool &);
    bool bool_or_not(String);
};
#endif
