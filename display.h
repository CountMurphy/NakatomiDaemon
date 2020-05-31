#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>

class Display
{
    public:
        void SetRGB(int[]);
        void init();
        void clear();
        void setLine(int);
        void writeString(std::string);
    private:
        void latch();
        void dictionary(char, int[]); //wtf, c++ cant return arrays? What is this the dark ages?
        int presets[11][3]={
            {100,0,0},//tron
            {0,0,255},//purple
            {255,0,0},//yellow
            {255,0,167},//gold tron
            {255,0,197}, //firefly
            {255,0,220},//amber
            {255,255,255},//off
            {0,255,255},//blue
            {255,0,255},//red
            {255,255,0},//green
            {0,255,0}//bluegreen
        };

        enum eColor{tron=0,purple=1,yellow=2,gold_tron=3,firefly=4,amber=5,off=6,blue=7, red=8,green=9,blue_green=10};
        int blueLed=22;
        int redLed=10;
        int greenLed=9;
};
#endif
