#include "irblaster.h"
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

void IRBlaster::init()
{
    //set IR pin
    std::cout<<"Setting pins...\n"<<std::endl;
    gpioSetMode(IRLEDpin, PI_OUTPUT);
    gpioWrite(IRLEDpin, 0); // Set low to start
    return;
}

void IRBlaster::setBT()
{
    IRsendCode(btCode);
    return;
}

void IRBlaster::setPi()
{
    IRsendCode(Line1Code);
    return;
}

//Private
void IRBlaster::IRcarrier(unsigned int IRtimemicroseconds)
{
    for(unsigned int i=0; i < (IRtimemicroseconds / 26); i++)
    {
        gpioWrite(IRLEDpin,1); //turn on the IR LED
        usleep(9);
        gpioWrite(IRLEDpin,0); //turn off the IR LED
        usleep(9);
    }
}

void IRBlaster::IRsendCode(unsigned long code)
{
    //send the leading pulse
    IRcarrier(9000);            //9ms of carrier
    usleep(4500);

    //send the user defined 4 byte/32bit code
    for (int i=0; i<32; i++)            //send all 4 bytes or 32 bits
    {
        IRcarrier(BITtime);               //turn on the carrier for one bit time
        if (code & 0x80000000)            //get the current bit by masking all but the MSB
            usleep(3 * BITtime);//a HIGH is 3 bit time periods
        else
            usleep(BITtime);//a LOW is only 1 bit time period
        code<<=1;                        //shift to the next bit for this byte
    }
    IRcarrier(BITtime);                 //send a single STOP bit.
}
