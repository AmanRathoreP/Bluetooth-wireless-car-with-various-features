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

// bool state = 0;
GUI_info gui_info;
motor motor_info;

Adafruit_PCD8544 lcd = gui_info.lcd;
// short x_axis=0, y_axis=0;
void setup()
{
  // Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  lcd.begin(21, 4);
  lcd.clearDisplay();
  lcd.display();
  //  Serial.begin(9600);
  // delay(10);

  Wire.begin(); // Initiating the Wire library

  Gyroscope(-1, -36); // Initiating the Gyroscope class
  Joystick(1);        // Initiating the Joystick class
  GUI(8);             // Initiating the GUI class
  // Blutooth();         // Initiating the Blutooth class

  GUI().set_score(50);
  //  GUI().reset_score();
  // bool lock_or_not=0;
}

void loop()
{

  Joystick(0).get_state(gui_info.input_state);
  Joystick(0).get_position(gui_info.x_axis, gui_info.y_axis);
  if (gui_info.input_state)
    Gyroscope(0).get_position(gui_info.x_axis, gui_info.y_axis, true);

  //  gui_info.input_state=state;
  //    gui_info.x_axis=x_axis;
  //      gui_info.y_axis=y_axis;
  //  gui_info.gui_option_selected='d';

  check_state(gui_info.gui_state);
  if ((!(gui_info.gui_state)) && (gui_info.gui_option_selected != 'm'))
  {
    //* axis values will used for calculating vechicle movement

    // GUI().menu_lock(gui_info.lcd);
    // lcd.clearDisplay();
    //     lcd.print("Menu and car movement is locked please unlock it!");
    //     lcd.display();

    get_motor_directions_and_speed(motor_info.motor_1_speed, motor_info.motor_1_terminal_1, motor_info.motor_1_terminal_2, motor_info.motor_2_speed, motor_info.motor_2_terminal_1, motor_info.motor_2_terminal_2, gui_info.x_axis, gui_info.y_axis, gui_info.input_state);
    send_motor_data(motor_info,gui_info.gui_state);
    GUI().display_data(gui_info, motor_info);
    motor_info.motor_1_speed = 0;
    motor_info.motor_1_terminal_1 = 0;
    motor_info.motor_1_terminal_2 = 0;
    motor_info.motor_2_speed = 0;
    motor_info.motor_2_terminal_1 = 0;
    motor_info.motor_2_terminal_2 = 0;
  }
  else
  {
    //* axis values will used for calculating menu movement
    String text_to_display = String(String(">FreePlay\n") + String(">LineBalancing\n") + String(">SpeedPlay\n") + String(">AvoidObstacle\n") + String(">Setings\n") + String(">DeveloperMode\n"));

    gui_info.lcd.clearDisplay();
    gui_info.lcd.setCursor(0, 0);
    gui_info.lcd.setTextColor(BLACK);
    gui_info.lcd.print(text_to_display);
    //  gui_info.lcd.display();

    //  gui_info.lcd.clearDisplay();
    GUI().display_data(gui_info, motor_info);
  }
}

void check_state(bool &gui_state) { gui_state = !(digitalRead(8)); }
void send_motor_data(motor motor_info,bool state)
{

  // String text_to_display = String("X = " + String(x_coordinate) + " Y = " + String(y_coordinate) + "  State = " + String(state) + " R = " + String(motor_1_terminal_1) + ", " + String(motor_1_terminal_2) + ", " + String(motor_1_speed) + " L = " + String(motor_2_terminal_1) + ", " + String(motor_2_terminal_2) + ", " + String(motor_2_speed));

  // Serial.println(text_to_display);
  // // Serial.println("\n\n");
  //  String text_to_display = "Nothing!!";
  //  Blutooth().motor_encode(motor_info, text_to_display);
  //  Blutooth().motor_decode(text_to_display, motor_info);
  //
  //  text_to_display = String("R = " + String(motor_info.motor_1_terminal_1) + ", " + String(motor_info.motor_1_terminal_2) + ", " + String(motor_info.motor_1_speed) + "\nL = " + String(motor_info.motor_2_terminal_1) + ", " + String(motor_info.motor_2_terminal_2) + ", " + String(motor_info.motor_2_speed));
  //  Serial.println(text_to_display);
  //  delay(10);

  Blutooth().write(motor_info,state);
}
