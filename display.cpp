#include "display.h"
#include <pigpio.h>
#include <unistd.h>


void Display::latch()
{
    gpioWrite(15, 1); // Set low to start
    usleep(20);
    gpioWrite(15, 0); // Set low to start
    usleep(20);
}

void Display::clear()
{
    gpioWrite(14, 0); // RS
    gpioWrite(18, 1); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 0); //5
    gpioWrite(12, 0); //6
    gpioWrite(16, 0); //7
    latch();
}

void Display::penis()
{
    //P
    gpioWrite(14, 1); 
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 1); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    latch();
    //e
    gpioWrite(14, 1); 
    gpioWrite(18, 1); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 1); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    latch();
    //n
    gpioWrite(14, 1);
    gpioWrite(18, 0); //0
    gpioWrite(23, 1); //1
    gpioWrite(24, 1); //2
    gpioWrite(25, 1); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    latch();
    //i
    gpioWrite(14, 1);
    gpioWrite(18, 1); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 1); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    latch();
    //s
    gpioWrite(14, 1);
    gpioWrite(18, 1); //0
    gpioWrite(23, 1); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 1); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 1); //6
    gpioWrite(16, 0); //7
    //latch
    latch();
}

void Display::init()
{

    eColor color = firefly;
    SetRGB(presets[color]);

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


    //set 8 bit mode, 4 lines
    gpioWrite(14, 0); // RS
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 1); //3
    gpioWrite(8, 1); //4
    gpioWrite(7, 1); //5
    gpioWrite(12, 0); //6
    gpioWrite(16, 0); //7
    latch();
    
    //turn on display
    gpioWrite(14, 0); // RS
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, 1); //2
    gpioWrite(25, 1); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 0); //5
    gpioWrite(12, 0); //6
    gpioWrite(16, 0); //7
    //latch
    latch();


}

void Display::SetRGB(int preset[])
{
    gpioPWM(blueLed, preset[0]);
    gpioPWM(redLed, preset[1]);
    gpioPWM(greenLed, preset[2]);
    return;
}
