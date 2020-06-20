#ifndef MPD_H
#define MPD_H
#include <mpd/client.h>
#include <string>

class Mpd
{
    public:
        struct song
        {
            std::string title;
            std::string album;
            std::string artist;
        };
        song getSongInfo();
        short getPlayPercentBlock();
        void play();
        void pause();
        Mpd(){
            conn = mpd_connection_new(NULL, 0, 0);
        }
    private:
        struct mpd_connection *conn;
};
#endif
