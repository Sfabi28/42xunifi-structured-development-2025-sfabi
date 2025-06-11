#include "password_validator.h"

PwStatus validate_password(const char *new_pw, const char *curr_pw)
{

    PwStatus res = 0;

    if (new_pw == NULL || curr_pw == NULL) {
        return (res + 1);
    }

    int i = 0;

    while (new_pw[i] && curr_pw[i])
    {
        if (new_pw[i] != curr_pw[i])
            break;
        i++;
    }

    if (!new_pw[i] && !curr_pw[i])
        return (res + 1);

    printf("here\n");
    i = 0;

    while (new_pw[i])
        i++;

    if (i < 8)
        return (res + 1);

    printf("here\n");

    i = 0;
    bool upper = false;
    bool lower = false;
    bool digit = false;
    bool special = false;

    while (new_pw[i])
    {
        if (new_pw[i] >= 'A' && new_pw[i] <= 'Z')
            upper = true;
        
        if (new_pw[i] >= 'a' && new_pw[i] <= 'z')
            lower = true;

        if (new_pw[i] >= '0' && new_pw[i] <= '9')
            digit = true;

        if (new_pw[i] == '@' || new_pw[i] == '#' || new_pw[i] == '$' || new_pw[i] == '%' || new_pw[i] == '^' || new_pw[i] == '&' || new_pw[i] == '*')
            special = true;

        i++;
    }

    printf("here\n");
    printf("upper: %d, lower: %d, digit: %d, special: %d\n", upper, lower, digit, special);
    if (upper && special && digit && lower)
        return res;
    return (res + 1);
}
