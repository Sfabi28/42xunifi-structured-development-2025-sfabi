#include "password_validator.h"

static PwStatus validate_password_similarities(const char *psw, PasswordHistory *history)
{
    for (int i = 0; i < history->count; i++) {
        int diff = 0;
        int j = 0;

        while (psw[j] && history->passwords[i][j]) {
            if (psw[j] != history->passwords[i][j])
                diff++;
            j++;
        }
        while (psw[j]) {
            diff++;
            j++;
        }
        while (history->passwords[i][j]) { 
            diff++;
            j++;
        }
        if (diff < 2)
            return 2;
    }

    printf("ok");
    return 0;
}

static void update_history(const char *pw, PasswordHistory *history) {
    int len = 0;
    while (pw[len]) len++;
    char *copy = malloc(len + 1);
    if (copy) {
        for (int i = 0; i < len; i++)
            copy[i] = pw[i];
        copy[len] = '\0';
    }
    if (history->count < 3) {
        history->passwords[history->count++] = copy;
    } else {
        free(history->passwords[0]);
        for (int i = 1; i < 3; i++)
            history->passwords[i - 1] = history->passwords[i];
        history->passwords[2] = copy;
    }
}

PwStatus validate_password(const char *new_pw, PasswordHistory *history)
{
    PwStatus result;

    if (history->count == 0) {
        result = validate_password_bases(new_pw, NULL);
        if (result >= 1)
            return result;
        update_history(new_pw, history);
        return 0;
    } else {
        result = validate_password_bases(new_pw, history->passwords[history->count - 1]);
        if (result >= 1)
            return result;
        result = validate_password_similarities(new_pw, history);
        if (result == 0)
            update_history(new_pw, history);
        return result;
    }
}