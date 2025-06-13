#include "playlist_creator.h"

struct Playlist *create_playlist(void)
{
    struct MoodSettings *mood = analyze_user_mood();
    if (!mood)
        return NULL;

    struct FilterSettings *filters = default_filters();
    if (!filters) {
        free_mood_settings(mood);
        return NULL;
    }

    int variations = get_mood_variations(mood);
    for (int i = 0; i < variations; ++i) {
        filters = refine_filters(filters);
        if (!filters) {
            free_mood_settings(mood);
            return NULL;
        }
    }

    struct SongData *song = NULL;
    if (filters_require_popular_song(filters))
        song = fetch_popular_song();
    else
        song = fetch_niche_song();

    if (!song) {
        free_filter_settings(filters);
        free_mood_settings(mood);
        return NULL;
    }

    struct Playlist *playlist = combine_with_mood_playlist(song, mood);

    free_song_data(song);
    free_filter_settings(filters);
    free_mood_settings(mood);

    return playlist;
}