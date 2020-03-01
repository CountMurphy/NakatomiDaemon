#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
    public:
        void SetRGB(int,int,int);
        void init();
    private:
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
        int blueLed=22;
        int redLed=10;
        int greenLed=9;
};
#endif
