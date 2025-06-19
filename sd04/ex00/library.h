
#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 1000

typedef struct s_book
{
    int     id;
    char    *title;
    char    *author;
}   t_book;

typedef struct s_library
{
    t_book  books[MAX_BOOKS];
    int     count;
}   t_library;

int         load_catalog(const char *filename, t_library *library);

int         search_by_title(const t_library *library, const char *substr);

int         search_by_author(const t_library *library, const char *substr);

void        free_library(t_library *library);

char        *ft_strtrim(const char *str);
char        *ft_strtolower(const char *str);
int         ft_strcasestr(const char *haystack, const char *needle);

#endif