#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

typedef int PwStatus;
PwStatus validate_password(const char *new_pw, const char *curr_pw);

#endif