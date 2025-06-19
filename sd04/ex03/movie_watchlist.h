
#ifndef MOVIE_WATCHLIST_H
#define MOVIE_WATCHLIST_H

#define MAX_MOVIES 1000

typedef struct s_movie
{
    int     id;
    char    *title;
    char    *genre;
    int     watched;      
    int     rating;      
    char    date_watched[11];
}   t_movie;

typedef struct s_movie_list
{
    t_movie movies[MAX_MOVIES];
    int     count;
    int     max_id;
}   t_movie_list;

typedef struct s_genre_stats
{
    char    *genre;
    int     watched_count;
    int     unwatched_count;
    float   avg_rating;
}   t_genre_stats;

int         load_movies(const char *filename, t_movie_list *list);

int         save_movies(const char *filename, const t_movie_list *list);

int         search_movies(const t_movie_list *list, const char *substr, int by_genre, int *indices, int *found_count);

int         filter_by_watched(const t_movie_list *list, int watched, int *indices, int *filtered_count);

int         add_movie(t_movie_list *list, const t_movie *new_movie);
int         mark_movie_watched(t_movie_list *list, int id, int rating, const char *date);
int         update_movie_info(t_movie_list *list, int id, const char *new_title, const char *new_genre);
int         delete_movie(t_movie_list *list, int id);

void        compute_stats(const t_movie_list *list);

char        *ft_strtrim(const char *str);
char        *ft_strtolower(const char *str);
int         ft_strcasestr(const char *haystack, const char *needle);
int         is_valid_id(int id, const t_movie_list *list);
int         is_valid_rating(int rating, int watched);
int         is_valid_date(const char *date);
int         is_valid_title(const char *title);
int         is_valid_genre(const char *genre);

#endif