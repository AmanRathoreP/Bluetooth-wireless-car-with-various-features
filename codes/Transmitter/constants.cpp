/*
Date ->          2022-02-16
Time ->          13:40:01
Day ->           Wednesday
Month Name ->    February
Unix Time ->     1644999001
File Name ->     "constants.cpp" when created i.e. on 2022-02-16
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Transmitter/Transmitter_code_1/constants.cpp" when created i.e. on 2022-02-16

This is a file which contains all the constants used in the Transmitter code
*/
#include <Adafruit_PCD8544.h>

#define Nokia5110_LCD_rst 2
#define Nokia5110_LCD_ce 3
#define Nokia5110_LCD_do 4
#define Nokia5110_LCD_din 5
#define Nokia5110_LCD_clk 6

#define ADXL345 0x53 // The ADXL345 sensor I2C address (can found in datasheet)


#define turning_speed_divide_constant 2


struct GUI_info{
  bool gui_state=0; //* defines that gui is selected or rc car movement is selected, 0 means gui movement is selected
  char gui_option_selected='m'; //* m means main home screen menu is selected
  Adafruit_PCD8544 lcd= Adafruit_PCD8544(Nokia5110_LCD_clk, Nokia5110_LCD_din, Nokia5110_LCD_do, Nokia5110_LCD_ce, Nokia5110_LCD_rst);
  bool input_state=0; //* defines joystick is selected or Gyroscope is seledted 0 means Joystick is selected
  short x_axis,y_axis;
    };

    struct motor
    {
      short motor_1_speed = 0;
      bool motor_1_terminal_1 = 0;
      bool motor_1_terminal_2 = 0;
      short motor_2_speed = 0;
      bool motor_2_terminal_1 = 0;
      bool motor_2_terminal_2 = 0;
    };