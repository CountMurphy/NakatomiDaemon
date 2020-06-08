#include "mpd.h"
#include <string>

Mpd::song Mpd::getSongInfo()
{
    struct mpd_song *msong;
    //mpd_send_list_queue_meta(conn);
    msong = mpd_run_current_song(conn);
    const char* title = mpd_song_get_tag(msong, MPD_TAG_TITLE, 0);
    const char* artist = mpd_song_get_tag(msong, MPD_TAG_ARTIST, 0);
    const char* album = mpd_song_get_tag(msong, MPD_TAG_ALBUM, 0);
    mpd_response_finish(conn);
    Mpd::song retVal;
    retVal.title=title;
    retVal.artist=artist;
    retVal.album=album;
    return retVal;
}

short Mpd::getPlayPercentBlock()
{
    mpd_status *status = mpd_run_status(conn);
    int pos = mpd_status_get_elapsed_ms(status)/1000;
    struct mpd_song *msong;
    msong = mpd_run_current_song(conn);
    int length = mpd_song_get_duration(msong);
    mpd_response_finish(conn);
    return ((int)((float)pos/((float)length)*100))/5;
}
