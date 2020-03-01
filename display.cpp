#include "display.h"
#include <pigpio.h>

void Display::init()
{
    gpioPWM(blueLed, 255);
    gpioPWM(redLed, 0);
    gpioPWM(greenLed, 197);
    while(1);
}

void Display::SetRGB(int R,int G,int B)
{
    return;
}
