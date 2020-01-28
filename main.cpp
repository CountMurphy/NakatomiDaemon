#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <string>

const std::string helpMsg="\nArguments are \n--daemon or -d to run as daemon\n--help for this menu\n --single or -s for quick test mode\n";

const std::string noArgs="\nPlease provide argument. See --help\n";

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
            std::cout<<"Running in single shot mode"<<std::endl;
        }else{
            std::cout<<"\nUnknown argument. Please see --help\n"<<std::endl;
            return 1;
        }
    }else{
        std::cout<<noArgs<<std::endl;
        return 1;
    }
    gpioInitialise();
    //set IR pin
    gpioSetMode(18, PI_OUTPUT);
    //set source switch pin
    return 0;
}
