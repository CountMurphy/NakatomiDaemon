#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "strings.h"
#include "irblaster.h"
#include "display.h"
#include "mpd.h"

static bool buttonDetect(int modes[])
{
    int value = gpioRead(2); //power
    if (value != modes[0])
    {
        modes[0]=value;
        return true;
    }
    value = gpioRead(3); //color
    if (value != modes[1])
    {
        modes[1]=value;
        return true;
    }
    value = gpioRead(4); //source
    if (value != modes[2])
    {
        modes[2]=value;
        return true;
    }
    value = gpioRead(26); //play/pause
    if (value != modes[3])
    {
        modes[3]=value;
        return true;
    }
    return false;
}

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
    display.setLine(1);
    display.writeString("        OK");
    display.setLine(2);
    sleep(1);
    display.writeString("    3");
    usleep(500000);
    display.writeString("    2");
    usleep(500000);
    display.writeString("    1");
    usleep(500000);
    display.setLine(3);
    display.writeString("     Lets Jam");
    sleep(1);
    display.clear();

    //set buttons to input
    gpioSetMode(2,PI_INPUT); //power
    gpioSetMode(3,PI_INPUT); //color
    gpioSetMode(4,PI_INPUT); //source
    gpioSetMode(26,PI_INPUT); //play/pause

    Mpd mpd;
    mpd.play();

    int modes[4] = {PI_HIGH,PI_HIGH, PI_HIGH, PI_HIGH};
    buttonDetect(modes);

    short preset = 0;
    std::string lastSong;
    Mpd::song songInfo; 
    short blockLevel=-1;
    short lastLoad = -1;
    while(1)
    {
        //btnMon
        if(modes[2]==PI_LOW)//source
        {
            mpd.pause();
            display.setLine(2);
            display.writeString("      BlueTooth");
            display.SetRGB(display.presets[Display::blue]);
            Ir.setBT();
            while(modes[2]==PI_LOW)
            {
                usleep(500);
                buttonDetect(modes);
            }
            Ir.setPi();
            mpd.play();
            display.clear();
            display.SetRGB(display.presets[Display::firefly]);
        }
        //power
        if(modes[0] == PI_LOW){
            mpd.pause();
            display.clear();
            sleep(1);
            display.writeString("See you");
            display.setLine(2);
            display.writeString("space cowboy...");
            return 0;
        }

        //color change
        if(modes[1] == PI_LOW)
        {
            display.SetRGB(display.presets[preset]);
            preset < 10? preset++:preset=0;
        }
        //play/pause
        if(modes[3]==PI_LOW)
        {
            if(mpd.isPlaying())
                mpd.play();
            else
                mpd.pause();
        }

        songInfo = mpd.getSongInfo();
        display.writeString(songInfo.title);
        lastSong = songInfo.title;
        display.setLine(2);
        display.writeString(songInfo.artist);
        display.setLine(3);
        display.writeString(songInfo.album);
        blockLevel=-1;
        lastLoad = -1;
        while(true)
        {
            //btnMon()
            if(buttonDetect(modes))
            {
                break;
            }
            blockLevel = mpd.getPlayPercentBlock();
            if(blockLevel<lastLoad && blockLevel==0)
                break;
            //if track changes at 0%, daemon fucks up
            if(blockLevel==0)
            {
                songInfo = mpd.getSongInfo();
                if(lastSong != songInfo.title)
                    break;
            }
            lastLoad=blockLevel;
            display.setLine(4);
            display.writeBlockChar(blockLevel);
        }
        if(modes[1]==PI_LOW || modes[3]==PI_LOW)
            continue;
        display.clear();
        sleep(1);
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
