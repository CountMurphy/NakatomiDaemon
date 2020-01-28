#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "strings.h"


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        std::string arg = argv[1];
        if(arg=="-d" || arg=="--daemon")
        {
            daemon(1,1);
        }else if(arg=="--help"){
            std::cout<<helpMsg<<std::endl;
            return 1;
        }else if(arg=="--single" || arg=="-s"){
            std::cout<<"Running in non daemon mode"<<std::endl;
        }else{
            std::cout<<"\nUnknown argument. Please see --help\n"<<std::endl;
            return 1;
        }
    }else{
        std::cout<<noArgs<<std::endl;
        return 1;
    }

    if(gpioInitialise()==PI_INIT_FAILED)
        return 1;
    std::cout<<logo<<std::endl<<std::endl<<std::endl;
    //set IR pin
    std::cout<<"Setting pins...\n"<<std::endl;
    gpioSetMode(18, PI_OUTPUT);
    //set source switch pin
    //
    //start listeners/interrupts if thats a thing
    //
    //run mpd client for screen
    //if source moves, ir blast classes
    //
    //class irblast-> init, set btl, set pi
    //class mpdclient -> poll mpd, set volume, get volume,play, pause, stop, next, prev, get artist, get album
    //class display -> print, rgbBacklight, clear, new line
    return 0;
}
