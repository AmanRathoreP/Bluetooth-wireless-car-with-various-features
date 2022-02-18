/*
Date ->          2022-02-16
Time ->          12:47:19
Day ->           Wednesday
Month Name ->    February
Unix Time ->     1644995839
File Name ->     "Transmitter_code_1.ino" when created i.e. on 2022-02-16
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Transmitter/Transmitter_code_1/Transmitter_code_1.ino" when created i.e. on 2022-02-16

In this tutorial, you will learn about how to interface an transmiter with receiver to control a rc blutooth car
*/

#include <Adafruit_PCD8544.h>
#include <Wire.h>

#include "constants.cpp"
#include "functions.h"


bool state = 0;
GUI_info gui_info;

Adafruit_PCD8544 lcd = gui_info.lcd;
short x_axis=0, y_axis=0;
void setup()
{
  // Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  lcd.begin(21, 4); lcd.clearDisplay();
  lcd.display();
//  Serial.begin(9600);
// delay(10);

  Wire.begin(); // Initiating the Wire library

  Gyroscope(-1, -36); // Initiating the Gyroscope class
  Joystick(1);        // Initiating the Joystick class
  GUI(8);            // Initiating the GUI class
}

void loop()
{
  gui_info.input_state=state;
    gui_info.x_axis=x_axis;
      gui_info.y_axis=y_axis;
//       gui_info.gui_option_selected='d';
  


  Joystick(0).get_state(state);
Joystick(0).get_position(x_axis, y_axis);
if (state)
   Gyroscope(0).get_position(x_axis, y_axis,true);  



check_state(gui_info.gui_state);
if ((!(gui_info.gui_state))&&(gui_info.gui_option_selected!='m')){
  //* axis values will used for calculating vechicle movement

bool motor_1_terminal_1,motor_1_terminal_2,motor_2_terminal_1,motor_2_terminal_2;
short motor_1_speed,motor_2_speed;
get_motor_directions_and_speed(motor_1_speed, motor_1_terminal_1, motor_1_terminal_2, motor_2_speed, motor_2_terminal_1, motor_2_terminal_2, x_axis, y_axis,state);
send_motor_data(motor_1_speed, motor_1_terminal_1, motor_1_terminal_2, motor_2_speed, motor_2_terminal_1, motor_2_terminal_2, x_axis, y_axis,state);
GUI().display_data(gui_info);
}else { 
  //* axis values will used for calculating menu movement
  
GUI().display_data(gui_info);
}
  
}

void check_state(bool &gui_state){    gui_state =!( digitalRead(8));}
void send_motor_data(short &motor_1_speed, bool &motor_1_terminal_1, bool &motor_1_terminal_2, short &motor_2_speed, bool &motor_2_terminal_1, bool &motor_2_terminal_2, short x_coordinate, short y_coordinate, bool state){}
