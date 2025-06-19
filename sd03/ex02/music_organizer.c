
#include "music_organizer.h"

struct MusicLibrary *organize_music_library(const char *directory_path)
{
    struct MusicLibrary *library = NULL;
    const char **files = NULL;

    library = create_music_library();
    if (!library)
        return NULL;
    files = scan_directory(directory_path);
    if (!files) {
        free(library);
        return NULL;
    }
    for (int i = 0; files[i] != NULL; ++i) {
        struct MusicFile *song = process_music_file(directory_path, files[i]);
        if (song)
            update_music_library(library, song);
    }
    for (int i = 0; files[i] != NULL; ++i)
        free((void *)files[i]);
    free((void *)files);

    return library;
}