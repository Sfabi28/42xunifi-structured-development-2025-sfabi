#include "contact_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Utility ---

static char *trim_spaces(const char *s)
{
    const char *start = s;
    const char *end;
    size_t len;
    char *res;

    while (*start && isspace((unsigned char)*start))
        start++;
    end = start + strlen(start);
    while (end > start && isspace((unsigned char)*(end - 1)))
        end--;
    len = end - start;
    res = malloc(len + 1);
    if (res) {
        strncpy(res, start, len);
        res[len] = '\0';
    }
    return res;
}

int is_valid_id(int id, const t_contact_list *list)
{
    int valid = 1;
    int i = 0;
    if (id <= 0)
        valid = 0;
    while (i < list->count && valid) {
        if (list->contacts[i].id == id)
            valid = 0;
        i++;
    }
    return valid;
}

int is_valid_name(const char *name)
{
    return (name && *name);
}

int is_valid_city(const char *city)
{
    return (city && *city);
}

int is_valid_phone(const char *phone)
{
    int digit_found = 0;
    int valid = 1;
    int i = 0;
    while (phone[i] && valid) {
        if (isdigit((unsigned char)phone[i]))
            digit_found = 1;
        else if (!strchr(" -()+.", phone[i]))
            valid = 0;
        i++;
    }
    if (!digit_found)
        valid = 0;
    return valid;
}

int is_valid_email(const char *email)
{
    const char *at = strchr(email, '@');
    int valid = 1;
    if (!at || at == email || !strchr(at, '.'))
        valid = 0;
    if (valid && (!at[1] || strchr(at + 1, '@')))
        valid = 0;
    return valid;
}

static int split_csv_fields(char *line, char **fields, int n)
{
    int i = 0;
    char *tmp = line;
    int ok = 1;
    while (i < n - 1 && ok) {
        fields[i] = tmp;
        tmp = strchr(tmp, ',');
        if (!tmp)
            ok = 0;
        else {
            *tmp = '\0';
            tmp++;
        }
        i++;
    }
    if (ok)
        fields[n - 1] = tmp;
    return ok;
}

static void free_contact(t_contact *c)
{
    free(c->name);
    free(c->phone);
    free(c->email);
    free(c->city);
    free(c->address);
}

void free_contact_list(t_contact_list *list)
{
    int i = 0;
    while (i < list->count) {
        free_contact(&list->contacts[i]);
        i++;
    }
}

// --- Caricamento e salvataggio ---

int load_contacts(const char *filename, t_contact_list *list)
{
    FILE *f;
    char buf[1024];
    int ok = 1;
    int count = 0;
    int max_id = 0;

    f = fopen(filename, "r");
    if (!f)
        ok = 0;
    if (ok) {
        while (fgets(buf, sizeof(buf), f) && count < MAX_CONTACTS) {
            char *line = buf;
            char *fields[6];
            char *trimmed[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
            int valid = 1;
            int id = 0;
            int i = 0;

            if (!split_csv_fields(line, fields, 6))
                valid = 0;

            i = 0;
            while (i < 6 && valid) {
                trimmed[i] = trim_spaces(fields[i]);
                if (!trimmed[i])
                    valid = 0;
                i++;
            }

            if (valid) {
                id = atoi(trimmed[0]);
                if (!is_valid_id(id, list))
                    valid = 0;
                if (!is_valid_name(trimmed[1]))
                    valid = 0;
                if (!is_valid_phone(trimmed[2]))
                    valid = 0;
                if (!is_valid_email(trimmed[3]))
                    valid = 0;
                if (!is_valid_city(trimmed[4]))
                    valid = 0;
            }

            if (valid) {
                t_contact *c = &list->contacts[count];
                c->id = id;
                c->name = trimmed[1];
                c->phone = trimmed[2];
                c->email = trimmed[3];
                c->city = trimmed[4];
                c->address = trimmed[5];
                if (id > max_id)
                    max_id = id;
                free(trimmed[0]);
                count++;
            } else {
                fprintf(stderr, "Warning: invalid contact skipped\n");
                i = 0;
                while (i < 6) {
                    free(trimmed[i]);
                    i++;
                }
            }
        }
        fclose(f);
    }
    list->count = count;
    list->max_id = max_id;
    return ok;
}

int save_contacts(const char *filename, const t_contact_list *list)
{
    FILE *f;
    int ok = 1;
    int i = 0;
    f = fopen(filename, "w");
    if (!f)
        ok = 0;
    if (ok) {
        while (i < list->count) {
            const t_contact *c = &list->contacts[i];
            fprintf(f, "%d,%s,%s,%s,%s,%s\n",
                c->id, c->name, c->phone, c->email, c->city, c->address ? c->address : "");
            i++;
        }
        fclose(f);
    }
    return ok;
}

// --- Ricerca ---

static int strcasestr_simple(const char *haystack, const char *needle)
{
    int found = 0;
    size_t nlen = strlen(needle);
    if (!*needle)
        found = 1;
    else {
        while (*haystack && !found) {
            if (strncasecmp(haystack, needle, nlen) == 0)
                found = 1;
            haystack++;
        }
    }
    return found;
}

int search_contacts(const t_contact_list *list, const char *substr, int by_city, int *indices, int *found_count)
{
    int found = 0;
    int i = 0;
    while (i < list->count) {
        const char *field = by_city ? list->contacts[i].city : list->contacts[i].name;
        if (strcasestr_simple(field, substr)) {
            indices[found] = i;
            found++;
        }
        i++;
    }
    if (found_count)
        *found_count = found;
    return found;
}

// --- Gestione contatti ---

int add_contact(t_contact_list *list, const t_contact *new_contact)
{
    int ok = 0;
    t_contact *c;
    if (list->count < MAX_CONTACTS) {
        c = &list->contacts[list->count];
        c->id = list->max_id + 1;
        c->name = strdup(new_contact->name);
        c->phone = strdup(new_contact->phone);
        c->email = strdup(new_contact->email);
        c->city = strdup(new_contact->city);
        c->address = new_contact->address ? strdup(new_contact->address) : strdup("");
        list->count++;
        list->max_id = c->id;
        ok = 1;
    }
    return ok;
}

int update_contact(t_contact_list *list, int id, const t_contact *updated_contact)
{
    int ok = 0;
    int i = 0;
    while (i < list->count && !ok) {
        if (list->contacts[i].id == id) {
            free_contact(&list->contacts[i]);
            list->contacts[i].id = id;
            list->contacts[i].name = strdup(updated_contact->name);
            list->contacts[i].phone = strdup(updated_contact->phone);
            list->contacts[i].email = strdup(updated_contact->email);
            list->contacts[i].city = strdup(updated_contact->city);
            list->contacts[i].address = updated_contact->address ? strdup(updated_contact->address) : strdup("");
            ok = 1;
        }
        i++;
    }
    return ok;
}

int delete_contact(t_contact_list *list, int id)
{
    int ok = 0;
    int i = 0;
    while (i < list->count && !ok) {
        if (list->contacts[i].id == id) {
            free_contact(&list->contacts[i]);
            int j = i;
            while (j < list->count - 1) {
                list->contacts[j] = list->contacts[j + 1];
                j++;
            }
            list->count--;
            ok = 1;
        }
        i++;
    }
    return ok;
}