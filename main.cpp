#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "strings.h"
#include "irblaster.h"
#include "display.h"
#include "mpd.h"


int main(int argc, char *argv[])
{
    if(gpioInitialise()==PI_INIT_FAILED)
    {
        std::cout<<helpMsg<<std::endl;
        return 1;
    }
    std::cout<<logo<<std::endl<<std::endl<<std::endl;

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
        }else if(arg=="--btle"){
            IRBlaster IrTmp;
            IrTmp.init();
            IrTmp.setBT();
            return 0;
        }else if(arg=="--line1"){
            IRBlaster IrTmp;
            IrTmp.init();
            IrTmp.setPi();
            return 0;
        }else{
            std::cout<<"\nUnknown argument. Please see --help\n"<<std::endl;
            return 1;
        }
    }else{
        std::cout<<noArgs<<std::endl;
    }


    IRBlaster Ir;
    Ir.init();
    Display display;
    display.init();
    display.clear();
    sleep(1);
    display.setLine(2);
    display.writeString("       Sarif");
    display.setLine(3);
    display.writeString("     Industries");
    sleep(5);
    display.clear();

    Mpd mpd;
    while(1)
    {
      Mpd::song songInfo = mpd.getSongInfo();
      display.writeString(songInfo.title);
      display.setLine(2);
      display.writeString(songInfo.artist);
      display.setLine(3);
      display.writeString(songInfo.album);
      short blockLevel=0;
      short lastLoad = 0;
      while(blockLevel!=20)
      {
          blockLevel = mpd.getPlayPercentBlock();
          if(blockLevel<lastLoad)
              break;
          lastLoad=blockLevel;
          display.setLine(4);
          display.writeBlockChar(blockLevel);
      }
      display.clear();
    }
    ////await knob turn to launch

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
