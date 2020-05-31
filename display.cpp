#include "display.h"
#include <pigpio.h>
#include <unistd.h>
#include <string>


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

void Display::setLine(int line)
{
    gpioWrite(14, 0); // RS
    gpioWrite(18, 0); //0
    gpioWrite(23, 0); //1
    gpioWrite(24, line==4 || line==3 ?1:0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, line==4 || line==3?1:0); //4
    gpioWrite(7, 0); //5
    gpioWrite(12, line==2 || line ==4? 1:0); //6
    gpioWrite(16, 1); //7
    latch();
}

void Display::writeString(std::string word)
{
    //get binary value
    for(unsigned int i = 0; i<word.length();i++)
    {
        int screenValues[8];
        dictionary(word[i], screenValues);
        gpioWrite(14, 1); // RS
        gpioWrite(18, screenValues[0]); //0
        gpioWrite(23, screenValues[1]); //1
        gpioWrite(24, screenValues[2]); //2
        gpioWrite(25, screenValues[3]); //3
        gpioWrite(8, screenValues[4]); //4
        gpioWrite(7, screenValues[5]); //5
        gpioWrite(12, screenValues[6]); //6
        gpioWrite(16, screenValues[7]); //7
        latch();
    }
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
    
    //set scroll
    //gpioWrite(14, 0); // RS
    //gpioWrite(18, 1); //0
    //gpioWrite(23, 1); //1 //if odd scrolling flip this
    //gpioWrite(24, 1); //2
    //gpioWrite(25, 0); //3
    //gpioWrite(8, 0); //4
    //gpioWrite(7, 0); //5
    //gpioWrite(12, 0); //6
    //gpioWrite(16, 0); //7
    //latch();
    
    //set home
    gpioWrite(14, 0); // RS
    gpioWrite(18, 0); //0
    gpioWrite(23, 1); //1
    gpioWrite(24, 0); //2
    gpioWrite(25, 0); //3
    gpioWrite(8, 0); //4
    gpioWrite(7, 0); //5
    gpioWrite(12, 0); //6
    gpioWrite(16, 0); //7
    
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

void Display::dictionary(char character, int retVal[])
{
    //retVal is passed by ref because c++ is retarded
    switch(character)
    {
        case 'e':
            retVal[0] = 1;
            retVal[1] = 0;
            retVal[2] = 1;
            retVal[3] = 0;
            retVal[4] = 0;
            retVal[5] = 1;
            retVal[6] = 1;
            retVal[7] = 0;
            break;
        case 'i':
            retVal[0] = 1;
            retVal[1] = 0;
            retVal[2] = 0;
            retVal[3] = 1;
            retVal[4] = 0;
            retVal[5] = 1;
            retVal[6] = 1;
            retVal[7] = 0;
            break;
        case 'n':
            retVal[0] = 0;
            retVal[1] = 1;
            retVal[2] = 1;
            retVal[3] = 1;
            retVal[4] = 0;
            retVal[5] = 1;
            retVal[6] = 1;
            retVal[7] = 0;
            break;
        case 'p':
            retVal[0] = 0;
            retVal[1] = 0;
            retVal[2] = 0;
            retVal[3] = 0;
            retVal[4] = 1;
            retVal[5] = 1;
            retVal[6] = 1;
            retVal[7] = 0;
            break;
        case 's':
            retVal[0] = 1;
            retVal[1] = 1;
            retVal[2] = 0;
            retVal[3] = 0;
            retVal[4] = 1;
            retVal[5] = 1;
            retVal[6] = 1;
            retVal[7] = 0;
            break;
    }
}
