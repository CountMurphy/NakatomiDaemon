#include "irblaster.h"
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

void IRBlaster::init()
{
    //set IR pin
    std::cout<<"Setting pins...\n"<<std::endl;
    gpioSetMode(BTLE_LEDpin, PI_OUTPUT);
    gpioSetMode(Line1_LEDpin, PI_OUTPUT);
    gpioWrite(BTLE_LEDpin, 0); // Set low to start
    gpioWrite(Line1_LEDpin, 0); // Set low to start
    return;
}

void IRBlaster::setBT()
{
    gpioWrite(BTLE_LEDpin,1);
    sleep(1);
    gpioWrite(BTLE_LEDpin,0);
    return;
}

void IRBlaster::setPi()
{
    gpioWrite(Line1_LEDpin,1);
    sleep(1);
    gpioWrite(Line1_LEDpin,0);
    return;
}

