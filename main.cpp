#include <pigpio.h>

int main()
{
    gpioInitialise();
    gpioSetMode(18, PI_OUTPUT);
    return 0;
}
