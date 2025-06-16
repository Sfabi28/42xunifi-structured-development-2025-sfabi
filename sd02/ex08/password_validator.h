#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

typedef int PwStatus;

typedef struct PasswordHistory {
    char **passwords;
    int count;
} PasswordHistory;

PwStatus validate_password_bases(const char *new_pw, const char *curr_pw);
PwStatus validate_password(const char *new_pw, PasswordHistory *history);

#endif