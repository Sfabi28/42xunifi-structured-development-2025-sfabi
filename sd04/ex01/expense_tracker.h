
#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#define MAX_EXPENSES 1000

typedef struct s_expense
{
    char    date[11];
    float   amount;
    char    *category;
    char    *description;
}   t_expense;

typedef struct s_expense_list
{
    t_expense   expenses[MAX_EXPENSES];
    int         count;
}   t_expense_list;

typedef struct s_category_summary
{
    char    *category;
    float   total;
    float   percentage;
    int     count;
}   t_category_summary;

int         load_expenses(const char *filename, t_expense_list *list);

int         filter_by_category(const t_expense_list *list, const char *substr, int *indices, int *filtered_count);

int         filter_by_date_range(const t_expense_list *list, const char *start, const char *end, int *indices, int *filtered_count);

char        *ft_strtrim(const char *str);
char        *ft_strtolower(const char *str);
int         ft_strcasestr(const char *haystack, const char *needle);
int         is_valid_date(const char *date);
int         is_valid_amount(const char *amount_str, float *amount);

#endif