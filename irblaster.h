#ifndef IRBLASTER_H
#define IRBLASTER_H

#define BITtime   562            //length of the carrier bit in microseconds

class IRBlaster
{
    public:
        void init();
        void setBT();
        void setPi();
        unsigned long btCode=0b00001000111001110111000010001111;
    private:
        void IRsendCode(unsigned long);
        void IRcarrier(unsigned int);
        short IRLEDpin=17;
};

#endif
