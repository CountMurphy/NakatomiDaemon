#include "display.h"
#include <pigpio.h>
#include <unistd.h>

void Display::init()
{
    gpioPWM(blueLed, 255);
    gpioPWM(redLed, 0);
    gpioPWM(greenLed, 197);

    gpioSetMode(14, PI_OUTPUT);//RS
    gpioSetMode(15, PI_OUTPUT);//E
    gpioSetMode(18, PI_OUTPUT);//Data 0
    gpioSetMode(23, PI_OUTPUT);//Data 1
    gpioSetMode(24, PI_OUTPUT);//Data 2
    gpioSetMode(25, PI_OUTPUT);//Data 3
    gpioSetMode(8, PI_OUTPUT);//Data 4
    gpioSetMode(7, PI_OUTPUT);//Data 5
    gpioSetMode(12, PI_OUTPUT);//Data 6
    gpioSetMode(16, PI_OUTPUT);//Data 7
    gpioWrite(15, 0); // Set low to start

    //turn on display
    gpioWrite(14, 0); // Set low to start
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 1); //2
    gpioWrite(25, 1); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 0); //5
    gpioWrite(12, 0); //6
    gpioWrite(16, 0); //7
    //latch
    gpioWrite(15, 1); // Set low to start
    gpioWrite(15, 0); // Set low to start
    //char
    gpioWrite(14, 1); // Set low to start
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 1); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    gpioWrite(15, 1); // Set low to start
    gpioWrite(15, 0); // Set low to start


    while(1);
}

void Display::SetRGB(int R,int G,int B)
{
    return;
}
