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
#include <Adafruit_PCD8544.h>
#include <string.h>
// #include <ArxContainer.h>
#include <EEPROM.h>

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

// void Gyroscope::get_position(float &x, float &y)
//{
//     }

void Gyroscope::get_position(int &x, int &y)
{
    //    float x_axis_value = x;
    //    float y_axis_value = y;
    get_position(x, y);
    //    x = (int)x_axis_value;
    //    y = (int)y_axis_value;
}
void Gyroscope::get_position(short &x, short &y, bool filter)
{
    //     int x_axis_value = x;
    //     int y_axis_value = y;
    //    get_position(x_axis_value, y_axis_value);
    //    x = (short)x_axis_value;
    //    y = (short)y_axis_value;

    Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 4, 1); // Note: I'm not using z value as my work can be done fine useing x and y values

    x = (Wire.read() | Wire.read() << 8); // X-axis value
    y = (Wire.read() | Wire.read() << 8); // Y-axis value

    if (filter)
        filter_values(x, y);
}

void Gyroscope::filter_values(short &x, short &y)
{
    if (x < (-260))
    {
        x = -259;
    }
    if (y < (-364))
    {
        y = -363;
    }

    if (x > 269)
    {
        x = 268;
    }
    if (y > 166)
    {
        y = 165;
    }

    x = map(x, -260, 269, -511, 511);
    y = map(y, -365, 166, -511, 511); //  y=map(y, -260, 269, 0, 1023);  // y=map(y, -310, 233, 0, 1024);

    if ((x > (-100)) && (x < 100))
    {
        x = 0;
    }
    if ((y > (-100)) && (y < 100))
    {
        y = 0;
    }

    if (y <= (-507))
    {
        y = -511;
    }
    else if ((y > 425) && (y <= 431))
    {
        y = 430;
    }

    // x *= (-1); //* to make things work in an systematic manner
    // y *= (-1); //* to make things work in an systematic manner
}

void Gyroscope::set_offset(short x_offset, short y_offset)
{

    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D); //* Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); //* (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    Wire.endTransmission();
    delay(10);

    //* x_axis offset calibration
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1E);     //* X-axis offset register
    Wire.write(x_offset); //* round(difference_of(256, incorrent value)/4)
    Wire.endTransmission();
    delay(10);
    //* y_axis offset calibration
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1F);     //* Y-axis offset register
    Wire.write(y_offset); //* round(difference_of(256, incorrent value)/4)
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

Joystick::Joystick(short x, short y, short state_pin)
{
    init(x, y, state_pin);
}
Joystick::Joystick(void)
{
    init(A0, A1, 7);
}
Joystick::Joystick(bool set_or_not)
{
    init(set_or_not);
}

void Joystick::get_position(short &x, short &y, bool &_state, short pin_x, short pin_y, short state_pin, bool filter)
{
    x = analogRead(pin_x);
    y = analogRead(pin_y);

    get_state(_state, state_pin);
    if (filter)
    {
        x = map(x, 0, 1023, -511, 511);
        y = map(y, 0, 1023, -511, 511);

        if ((x > (-50)) && (x < 50))
        {
            x = 0;
        }
        if ((y > (-50)) && (y < 50))
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
{
    bool fake_state = 0;
    get_position(x, y, fake_state, A0, A1, 7, 1);
}
void Joystick::get_state(bool &_state, short state_pin)
{
    if (!(digitalRead(state_pin)))
    {
        _state = !_state;
    }
    delay(100);
}
void Joystick::get_state(bool &_state)
{
    get_state(_state, 7);
}
void Joystick::init(void)
{
    init(A0, A1, 7);
}
void Joystick::init(short x_pin, short y_pin, short state_pin)
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
            motor_1_speed = (y_coordinate + (x_coordinate * (-1))) / turning_speed_divide_constant;
        }
        else if (x_coordinate > 0)
        { //* Going forward+right turn
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = (y_coordinate + x_coordinate) / turning_speed_divide_constant;
        }
    }
    else if (y_coordinate < 0)
    {
        //* Going backword+turning
        if (x_coordinate < 0)
        { //* Going backword+left turn
            __terminal_value__('l', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = ((y_coordinate + x_coordinate) * (-1)) / turning_speed_divide_constant;
        }
        else if (x_coordinate > 0)
        { //* Going backword+right turn
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = ((y_coordinate * (-1)) + x_coordinate) / turning_speed_divide_constant;
        }
    }
    if (y_coordinate == 0)
    {
        //* just turning without moving forward or backwards
        if (x_coordinate < 0)
        {
            //* Turn Left
            __terminal_value__('l', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = (x_coordinate * (-1)) + 511;
        }
        else if (x_coordinate > 0)
        {
            //* Turn Right
            __terminal_value__('r', motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
            motor_1_speed = x_coordinate + 511;
        }
    }

    motor_2_speed = motor_1_speed;

    if (state && (motor_1_speed != 0))
    {
        __change_direction__(motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2);
    }
}
void __terminal_value__(char direction_to_turn, bool &motor_1_terminal_1, bool &motor_1_terminal_2, bool &motor_2_terminal_1, bool &motor_2_terminal_2)
{
    switch (direction_to_turn)
    {
    case 'l': //* for Right
        motor_1_terminal_1 = 1;
        motor_1_terminal_2 = 0;
        motor_2_terminal_1 = 0;
        motor_2_terminal_2 = 1;
        break;
    case 'r': //* for Left
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

//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes
//! Note: This is the start of gui classes

GUI::GUI(GUI_info &gui_info)
{
    GUI(gui_info, 8);
}
GUI::GUI(GUI_info &gui_info, short pin)
{
    gui_info.gui_state = !(digitalRead(pin));
}
GUI::GUI(short pin)
{
    pinMode(pin, INPUT);
}
GUI::GUI(void) {}

void GUI::get_home_screen(GUI_info &gui_info)
{

    if (gui_info.gui_state)
    {
        gui_info.input_state = 0;
        static char joystick_position = 'l'; //* l means low, h means high ; it will help to only select option when joystick make transition from low to high so that if joystick leave high then no other option will be selected until it is again set to low
        static short menu_item = 0;
        // Joystick(0).get_position(gui_info.x_axis, gui_info.y_axis);

        if ((gui_info.y_axis >= 490) && (joystick_position == 'l'))
        {
            menu_item--;
            joystick_position == 'h';
        }
        else if ((gui_info.y_axis <= (-490)) && (joystick_position == 'l'))
        {
            menu_item++;
            joystick_position == 'h';
        }
        if (menu_item <= -1)
            menu_item = 5;
        else if (menu_item >= 6)
            menu_item = 0;

        String text_to_display_array[6] = {String(">FreePlay\n"), String(">LineBalancing\n"), String(">SpeedPlay\n"), String(">AvoidObstacle\n"), String(">Setings\n"), String(">DeveloperMode\n")};

        // String text_to_display = String(String(">FreePlay\n") + String(">LineBalancing\n") + String(">SpeedPlay\n") + String(">AvoidObstacle\n") + String(">Setings\n") + String(">DeveloperMode\n"));

        // gui_info.lcd.clearDisplay();
        // gui_info.lcd.setCursor(0, 0);
        // gui_info.lcd.setTextColor(BLACK);
        // gui_info.lcd.print(text_to_display);
        // gui_info.lcd.display();

        // gui_info.lcd.clearDisplay();
        gui_info.lcd.setCursor(0, (8 * menu_item));
        gui_info.lcd.setTextColor(WHITE, BLACK);
        gui_info.lcd.print(String(text_to_display_array[menu_item]));
        gui_info.lcd.setTextColor(BLACK);
        gui_info.lcd.display();

        Joystick(0).get_state(gui_info.input_state);
        if ((gui_info.input_state) == 1)
        {
            switch (menu_item)
            {
            case 0:
                //* FreePlay is selected
                gui_info.gui_option_selected = 'f';
                break;
            case 1:
                //* LineBalancing is selected
                gui_info.gui_option_selected = 'l';
                break;
            case 2:
                //* SpeedPlay is selected
                gui_info.gui_option_selected = 'p';
                break;
            case 3:
                //* AvoidObstacle is selected
                gui_info.gui_option_selected = 'o';
                break;
            case 4:
                //* Setings is selected
                gui_info.gui_option_selected = 's';
                break;
            case 5:
                //* DeveloperMode is selected
                gui_info.gui_option_selected = 'd';
                break;

            default:
                //* let it be main menu
                gui_info.gui_option_selected = 'm';
                break;
            }
        }
    }
}

void GUI::display_data(GUI_info &gui_info, motor &motor_info)
{
    switch (gui_info.gui_option_selected)
    {
    case 'f':
        //* FreePlay is selected
        FreePlay(gui_info, motor_info);
        //! gui_info.gui_option_selected = 'f';
        break;
    case 'l':
        //* LineBalancing is selected
        LineBalancing(gui_info, motor_info);
        //! gui_info.gui_option_selected = 'l';
        break;
    case 'p':
        //* SpeedPlay is selected
        SpeedPlay(gui_info, motor_info);
        //! gui_info.gui_option_selected = 'p';
        break;
    case 'o':
        //* AvoidObstacle is selected
        AvoidObstacle(gui_info);
        //! gui_info.gui_option_selected = 'o';
        break;
    case 's':
        //* Setings is selected
        Setings(gui_info);
        //! gui_info.gui_option_selected = 's';
        break;
    case 'd':
        //* DeveloperMode is selected
        DeveloperMode(gui_info, motor_info);
        //! gui_info.gui_option_selected = 'd';
        break;

    default:
        //* let it be main menu
        get_home_screen(gui_info);
        //! gui_info.gui_option_selected = 'm';
        break;
    }
}
void GUI::DeveloperMode(GUI_info &gui_info, motor &motor_info)
{
    // bool motor_1_terminal_1, motor_1_terminal_2, motor_2_terminal_1, motor_2_terminal_2;
    // short motor_1_speed, motor_2_speed;

    // get_motor_directions_and_speed(motor_1_speed, motor_1_terminal_1, motor_1_terminal_2, motor_2_speed, motor_2_terminal_1, motor_2_terminal_2, gui_info.x_axis, gui_info.y_axis, gui_info.input_state);

    String text_to_display = String("X = " + String(gui_info.x_axis) + "\nY = " + String(gui_info.y_axis) + "\nState = " + String(gui_info.input_state) + "\nR = " + String(motor_info.motor_1_terminal_1) + ", " + String(motor_info.motor_1_terminal_2) + ", " + String(motor_info.motor_1_speed) + "\nL = " + String(motor_info.motor_2_terminal_1) + ", " + String(motor_info.motor_2_terminal_2) + ", " + String(motor_info.motor_2_speed) + "\nLock = " + String(gui_info.gui_state));

    gui_info.lcd.clearDisplay();
    gui_info.lcd.setCursor(0, 0);
    gui_info.lcd.print(text_to_display);
    gui_info.lcd.display();
    // delay(10);
}

void GUI::Setings(GUI_info &gui_info)
{
    while (1)
    {
        gui_info.input_state = 0;
        Joystick(0).get_state(gui_info.input_state);
        static short contrast = 21;
        static char joystick_position = 'l'; //* l means low, h means high ; it will help to only select option when joystick make transition from low to high so that if joystick leave high then no other option will be selected until it is again set to low

        Joystick(0).get_position(gui_info.x_axis, gui_info.y_axis);
        if ((gui_info.y_axis >= 490) && (joystick_position == 'l'))
        {
            contrast++;
            joystick_position == 'h';
        }
        else if ((gui_info.y_axis <= (-490)) && (joystick_position == 'l'))
        {
            contrast--;
            joystick_position == 'h';
        }

        if ((gui_info.input_state) == 1)
        {
            gui_info.gui_option_selected = 'm';
            break;
        }

        gui_info.lcd.begin(contrast, 4);
        gui_info.lcd.clearDisplay();
        gui_info.lcd.setCursor(10, 10);
        gui_info.lcd.setTextSize(5);
        gui_info.lcd.print(String(contrast, DEC));
        gui_info.lcd.setCursor(0, 0);
        gui_info.lcd.setTextSize(1);
        gui_info.lcd.print(" Set Contrast ");
        gui_info.lcd.setCursor(0, 0);
        gui_info.lcd.display();
    }
}
void GUI::FreePlay(GUI_info &gui_info, motor &motor_info)
{
    // gui_info.input_state = 0;
    // Joystick(0).get_state(gui_info.input_state);
    if (!(gui_info.input_state))
    { //* Joystick is selected

        // Joystick(0).get_position(gui_info.x_axis, gui_info.y_axis);
        draw_stuff(gui_info, "Joystick");
    }
    else
    { //* Gyroscope is selected
        // Gyroscope(0).get_position(gui_info.x_axis, gui_info.y_axis, true);
        draw_stuff(gui_info, "Gyroscope");
    }
}
void GUI::draw_stuff(GUI_info &gui_info, String name)
{

    gui_info.lcd.clearDisplay();
    gui_info.x_axis = map(gui_info.x_axis, -511, 511, 2, 82);
    gui_info.y_axis = map(gui_info.y_axis, 511, -511, 2, 46);
    gui_info.lcd.fillCircle(gui_info.x_axis, gui_info.y_axis, 1, BLACK);
    if ((gui_info.x_axis <= 60) && (gui_info.y_axis <= 10))
    {
        gui_info.lcd.setCursor(20, 20);
        gui_info.lcd.print(name);
        // gui_info.lcd.setCursor(0, 0);
    }
    else
    {
        gui_info.lcd.setCursor(20, 0);
        gui_info.lcd.print(name);
    }

    gui_info.lcd.display();
    gui_info.lcd.clearDisplay();
}
void GUI::SpeedPlay(GUI_info &gui_info, motor &motor_info)
{
    long user_score = 0;
    long max_score = 0;
    get_previous_score(max_score);
    gui_info.lcd.clearDisplay();
    gui_info.lcd.fillRect(0, 0, 84, (48 / 2) + 1, 1);
    gui_info.lcd.setCursor(0, 1);
    gui_info.lcd.setTextColor(WHITE);
    if (!(gui_info.input_state))
    { //* Joystick is selected
        gui_info.lcd.print("   Joystick\n");
    }
    else
    { //* Gyroscope is selected
        gui_info.lcd.print("   Gyroscope\n");
    }
    gui_info.lcd.print("  Max Score   \n  ");
    gui_info.lcd.println(max_score);

    static long score = 0;
    if (gui_info.gui_state == 1)
    { //* Do not change score as the rc car movement is not selected
    }
    else if (((motor_info.motor_1_speed) >= 300) && (((motor_info.motor_1_terminal_1 == 0) && (motor_info.motor_1_terminal_2 == 1) && (motor_info.motor_2_terminal_1 == 0) && (motor_info.motor_2_terminal_2 == 1)) || ((motor_info.motor_1_terminal_1 == 1) && (motor_info.motor_1_terminal_2 == 0) && (motor_info.motor_2_terminal_1 == 1) && (motor_info.motor_2_terminal_2 == 0))))
    {
        //* Means car speed is greater than 300 and it is not rotating on it's own axis
        score++;
    }
    else if (((motor_info.motor_1_speed) >= 700) && (((motor_info.motor_1_terminal_1 == 0) && (motor_info.motor_1_terminal_2 == 1) && (motor_info.motor_2_terminal_1 == 0) && (motor_info.motor_2_terminal_2 == 1)) || ((motor_info.motor_1_terminal_1 == 1) && (motor_info.motor_1_terminal_2 == 0) && (motor_info.motor_2_terminal_1 == 1) && (motor_info.motor_2_terminal_2 == 0))))
    {
        //* Means car speed is greater than 700 and it is not rotating on it's own axis
        score += 2;
    }
    else if (((motor_info.motor_1_speed) <= 250) && (score > 0))
    {
        score--;
    }

    // user_score = (((motor_info.motor_1_speed) + (motor_info.motor_2_speed)) / 2) / ((millis() / 1000) - time_begin);
    user_score = score;
    gui_info.lcd.setTextColor(BLACK);
    gui_info.lcd.print("\n  Your Score  \n  ");
    store_score(user_score);
    gui_info.lcd.print(user_score);
    // gui_info.lcd.print(motor_info.motor_1_speed);
    gui_info.lcd.display();
    gui_info.lcd.clearDisplay();
}
void GUI::get_previous_score(long &score)
{
    get_long_from_eeprom(50, score);
}
void GUI::store_score(long score)
{
    // static bool previously_called_or_not = false;
    long previous_score = 0;
    get_previous_score(previous_score);
    if (score > previous_score)
    {
        store_long_in_eeprom(50, score);
    }
}
void GUI::store_long_in_eeprom(short address, long data)
{
    EEPROM.update(address, (data >> 24) & 0xFF);
    EEPROM.update(address + 1, (data >> 16) & 0xFF);
    EEPROM.update(address + 2, (data >> 8) & 0xFF);
    EEPROM.update(address + 3, data & 0xFF);
}
void GUI::get_long_from_eeprom(short address, long &data)
{
    data = ((long)EEPROM.read(address) << 24) + ((long)EEPROM.read(address + 1) << 16) + ((long)EEPROM.read(address + 2) << 8) + (long)EEPROM.read(address + 3);
}
void GUI::set_score(long data)
{
    store_long_in_eeprom(50, data);
}
void GUI::reset_score(void)
{
    set_score(0);
}
void GUI::menu_lock(Adafruit_PCD8544 lcd)
{
    lcd.clearDisplay();
    lcd.print("Menu and car movement is locked please unlock it!");
    lcd.display();
}
void GUI::LineBalancing(GUI_info &gui_info, motor &motor_info)
{
    //  gui_info.gui_option_selected = 'm';
    static bool state_when_came = (bool)gui_info.input_state;
    gui_info.lcd.clearDisplay();
    gui_info.lcd.setCursor(0, 1);
        gui_info.lcd.setTextColor(0);
gui_info.lcd.fillRect(0, 0,84,48, 1);
    // int delay_time = 1000;
    // delay(delay_time);

    gui_info.lcd.println("    Work in      Progress!!");
    gui_info.lcd.drawBitmap((gui_info.lcd.width() / 4) - 3, 0, image_work_in_progress, 48, 48, 0);
    gui_info.lcd.display();
    gui_info.lcd.clearDisplay();
    gui_info.lcd.setTextColor(1);

    if (gui_info.input_state != state_when_came)
    { //* Joystick switch is pressed
        gui_info.gui_option_selected = 'm';
    }
}

void GUI::get_distance_away_from(int &right_distance, int &left_distance)
{
    InterfaceSensor().get_distance(right_distance, left_distance);
}
void InterfaceSensor::init_ultra_sonic()
{
    pinMode(9, OUTPUT);
    pinMode(10, INPUT);
    pinMode(11, OUTPUT);
    pinMode(12, INPUT);
}
void InterfaceSensor::get_distance(int &right_distance, int &left_distance)
{
    static bool called_or_not = false;
    if (!called_or_not)
    {
        //* function is called for first time i.e. we need to init the sensor i.e. we need to define the pinMode
        init_ultra_sonic();
        called_or_not = true;
    }
    digitalWrite(11, HIGH);
    delay(1);
    digitalWrite(11, LOW);
    right_distance = (int)(((pulseIn(12, HIGH)) / 2) * (1 / 29.1));
    digitalWrite(9, HIGH);
    delay(1);
    digitalWrite(9, LOW);
    left_distance = (int)(((pulseIn(10, HIGH)) / 2) * (1 / 29.1));
}
void GUI::AvoidObstacle(GUI_info &gui_info)
{
    /*
    int right_distance = 0, left_distance = 0;

    get_distance_away_from(right_distance, left_distance);

    if (right_distance > 35)
        right_distance = 35;
    if (left_distance > 35)
        left_distance = 35;

    int right_graph_level = map(right_distance, 0, 35, 42, 0);
    int left_graph_level = map(left_distance, 0, 35, 42, 0);

    if (right_graph_level == 0)
        right_graph_level = 1;
    if (left_graph_level == 0)
        left_graph_level = 1;

    gui_info.lcd.clearDisplay();
    gui_info.lcd.fillRect(42, 0, right_graph_level, 39, BLACK);
    gui_info.lcd.fillRect(0 + (42 - left_graph_level), 0, left_graph_level, 39, BLACK);
    if (!(gui_info.input_state))
    { //* Joystick is selected
        gui_info.lcd.print("\n\n\n\n\n   Joystick");
    }
    else
    { //* Gyroscope is selected
        gui_info.lcd.print("\n\n\n\n\n   Gyroscope");
    }
    // gui_info.lcd.print("\n\n\n\nRight = ");
    // gui_info.lcd.println(right_distance);
    // gui_info.lcd.print("Left = ");
    // gui_info.lcd.println(left_distance);
    gui_info.lcd.display();
    */

    static bool state_when_came = (bool)gui_info.input_state;
    gui_info.lcd.clearDisplay();
    gui_info.lcd.setCursor(0, 1);

    // int delay_time = 1000;
    // delay(delay_time);

    gui_info.lcd.println("    Work in      Progress!!");
    gui_info.lcd.drawBitmap((gui_info.lcd.width() / 4) - 3, 0, image_work_in_progress, 48, 48, 1);
    gui_info.lcd.display();
    gui_info.lcd.clearDisplay();

    if (gui_info.input_state != state_when_came)
    { //* Joystick switch is pressed
        gui_info.gui_option_selected = 'm';
    }
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
    if (Serial.available() > 0)
    {
        data = Serial.readString().substring(0, 12);
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
    data_struct.motor_1_speed = (short )String(data_string.substring(2, 6)).toInt();
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
    __write(String(data_str)+"t");
}
