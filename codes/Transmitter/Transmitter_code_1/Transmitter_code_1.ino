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

Adafruit_PCD8544 lcd = Adafruit_PCD8544(Nokia5110_LCD_clk, Nokia5110_LCD_din, Nokia5110_LCD_do, Nokia5110_LCD_ce, Nokia5110_LCD_rst);
bool state = 0;
void setup()
{
  // Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  lcd.begin(21, 4);
  Wire.begin(); // Initiating the Wire library

  Gyroscope(-1, -9); // Initiating the Gyroscope class
  Joystick(1);       // Initiating the Joystick class
}

void loop()
{
  short x_axis, y_axis;

  Joystick(0).get_state(state);Gyroscope(0).get_position(x_axis, y_axis);  
if (state)
  Joystick(0).get_position(x_axis, y_axis);



  //  lcd.print("X = ");
  //  lcd.println(x_axis);
  //  lcd.print("Y = ");
  //  lcd.println(y_axis);
  //  lcd.print("State = ");
  //  lcd.println(state);

  lcd.print("X = ");
  lcd.println(x_axis);
  lcd.print("Y = ");
  lcd.println(y_axis);
  lcd.print("State = ");
  lcd.println(state);

  lcd.display();
  delay(10);
  lcd.clearDisplay();
  lcd.setCursor(0, 0);
}
