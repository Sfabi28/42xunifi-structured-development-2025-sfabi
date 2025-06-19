#include "password_validator.h"

int check_same_password(const char *new_pw, const char *curr_pw)
{
    int i = 0;

    if (curr_pw == NULL)
        return 0;

    while (new_pw[i] == curr_pw[i])
    {
        if (new_pw[i] == '\0' && curr_pw[i] == '\0')
            return 1;
        i++;
    }
    return 0;
}

int check_pass_length(const char *new_pw)
{
    int i = 0;

    while (new_pw[i])
        i++;

    return i;
}

int check_character_type(const char *new_pw)
{
    int i = 0;
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    
    while (new_pw[i])
    {
        if (new_pw[i] >= 'A' && new_pw[i] <= 'Z')
            has_upper = 1;
        else if (new_pw[i] >= 'a' && new_pw[i] <= 'z')
            has_lower = 1;
        else if (new_pw[i] >= '0' && new_pw[i] <= '9')
            has_digit = 1;
        else if (new_pw[i] == '@' || new_pw[i] == '#' || new_pw[i] == '$' || new_pw[i] == '%' || new_pw[i] == '^' || new_pw[i] == '&' || new_pw[i] == '*')
            has_special = 1;

        i++;
    }

    if (has_upper && has_lower && has_digit && has_special)
        return 0;
    return 1;
}

PwStatus validate_password_bases(const char *new_pw, const char *curr_pw)
{

    PwStatus res = 0;

    if (new_pw == NULL)
        return (res + 1);

    if (check_same_password(new_pw, curr_pw))
        return (res + 1);

    if (check_pass_length(new_pw) < 8)
        return (res + 1);

    res = check_character_type(new_pw);

    printf("Password validation result: %d\n", res);
    return res;
}
