/*
Date ->          2022-02-21
Time ->          13:38:41
Day ->           Monday
Month Name ->    February
Unix Time ->     1645430921
File Name ->     "functions.h" when created i.e. on 2022-02-21
File Path ->     "C:/Google Drive/Electronics/MicroControllers/tp pratice/2022-02-16 [arduino with RC Blutooth Car with diffrent features]/codes/Receiver/Receiver_code_1/functions.h" when created i.e. on 2022-02-21

This is just a header file and may you know why is this here
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void motor_controller(motor);
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
