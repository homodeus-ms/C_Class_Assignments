#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "user.h"

#define TRUE (1)
#define FALSE (0)

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

int update_email(user_t** users_or_null, unsigned int id, const char* email);

int update_password(user_t** users_or_null, unsigned int id, const char* password);

#endif /* DATA_STORE_H */
