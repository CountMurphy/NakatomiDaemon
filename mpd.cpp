#include "mpd.h"
#include <string>

Mpd::song Mpd::getSongInfo()
{
    struct mpd_song *msong;
    //mpd_send_list_queue_meta(conn);
    msong = mpd_run_current_song(conn);
    Mpd::song retVal;
    if(msong == NULL)
    {
        // Play list is clear
        retVal.title = "No Song Info";
        retVal.album = "";
        retVal.artist = "";
    }else{
        const char* title = mpd_song_get_tag(msong, MPD_TAG_TITLE, 0);
        const char* artist = mpd_song_get_tag(msong, MPD_TAG_ARTIST, 0);
        const char* album = mpd_song_get_tag(msong, MPD_TAG_ALBUM, 0);
        mpd_response_finish(conn);
        retVal.title=title == NULL ? "" : title;
        retVal.artist=artist == NULL ? "" : artist;
        retVal.album=album == NULL ? "" : album;
        mpd_song_free(msong);
    }
    return retVal;
}

void Mpd::play()
{
    //Connections close after inactivity. Check it first
    if(!mpd_run_play(conn))
    {
        mpd_connection_free(conn);
        conn = mpd_connection_new(NULL, 0, 0);
        mpd_run_play(conn);
    }
}

void Mpd::pause()
{
    mpd_run_pause(conn,true);
}

bool Mpd::isPlaying()
{
    mpd_status * servStatus = NULL;
    mpd_send_status(conn);
    servStatus = mpd_recv_status(conn);
    mpd_state current_status = mpd_status_get_state(servStatus);
    mpd_response_finish(conn);
    mpd_status_free(servStatus);
    return current_status==MPD_STATE_PAUSE;
}



short Mpd::getPlayPercentBlock()
{
    mpd_status *status = mpd_run_status(conn);
    int pos = mpd_status_get_elapsed_ms(status)/1000;
    struct mpd_song *msong;
    msong = mpd_run_current_song(conn);
    if(msong == NULL)
        return 0;
    int length = mpd_song_get_duration(msong);
    mpd_response_finish(conn);
    mpd_status_free(status);
    mpd_song_free(msong);
    return (((float)pos/(float)length)*100>=97) ? 20:((int)((float)pos/((float)length)*100))/5;
}

