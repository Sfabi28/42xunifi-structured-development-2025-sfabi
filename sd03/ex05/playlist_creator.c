#include "playlist_creator.h"

static struct FilterSettings *prepare_filters(struct MoodSettings *mood, int *error)
{
    struct FilterSettings *filters = default_filters();
    if (!filters) {
        *error = 1;
        return NULL;
    }

    int variations = get_mood_variations(mood);
    int i = 0;
    while (i < variations && *error == 0) {
        struct FilterSettings *new_filters = refine_filters(filters);
        if (!new_filters) {
            *error = 1;
        } else {
            filters = new_filters;
        }
        i++;
    }
    return filters;
}

static struct SongData *choose_song(struct FilterSettings *filters)
{
    if (filters_require_popular_song(filters))
        return fetch_popular_song();
    else
        return fetch_niche_song();
}

struct Playlist *create_playlist(void)
{
    struct MoodSettings *mood = NULL;
    struct FilterSettings *filters = NULL;
    struct SongData *song = NULL;
    struct Playlist *playlist = NULL;
    int error = 0;

    mood = analyze_user_mood();
    if (!mood)
        error = 1;

    if (!error)
        filters = prepare_filters(mood, &error);

    if (!error)
        song = choose_song(filters);

    if (!error && !song)
        error = 1;

    if (!error)
        playlist = combine_with_mood_playlist(song, mood);

    if (song)
        free_song_data(song);
    if (filters)
        free_filter_settings(filters);
    if (mood)
        free_mood_settings(mood);

    if (error)
        playlist = NULL;

    return playlist;
}