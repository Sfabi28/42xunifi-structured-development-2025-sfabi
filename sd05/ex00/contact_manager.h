
#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#define MAX_CONTACTS 1000

typedef struct s_contact
{
    int     id;
    char    *name;
    char    *phone;
    char    *email;
    char    *city;
    char    *address;
}   t_contact;

typedef struct s_contact_list
{
    t_contact    contacts[MAX_CONTACTS];
    int          count;
    int          max_id;
}   t_contact_list;

int         load_contacts(const char *filename, t_contact_list *list);

int         save_contacts(const char *filename, const t_contact_list *list);

int         search_contacts(const t_contact_list *list, const char *substr, int by_city, int *indices, int *found_count);

void        free_contact_list(t_contact_list *list);

int         add_contact(t_contact_list *list, const t_contact *new_contact);
int         update_contact(t_contact_list *list, int id, const t_contact *updated_contact);
int         delete_contact(t_contact_list *list, int id);

char        *ft_strtrim(const char *str);
char        *ft_strtolower(const char *str);
int         ft_strcasestr(const char *haystack, const char *needle);
int         is_valid_id(int id, const t_contact_list *list);
int         is_valid_phone(const char *phone);
int         is_valid_email(const char *email);
int         is_valid_name(const char *name);
int         is_valid_city(const char *city);

#endif