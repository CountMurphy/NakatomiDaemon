#ifndef IRBLASTER_H
#define IRBLASTER_H

#define BITtime   562            //length of the carrier bit in microseconds

class IRBlaster
{
    public:
        void init();
        void setBT();
        void setPi();
    private:
        short BTLE_LEDpin=17;
        short Line1_LEDpin=27;
};

#endif
