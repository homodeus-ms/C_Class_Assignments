#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id)
{
    if (users_or_null == NULL) {
        return NULL;
    }

    user_t** pp;
    pp = users_or_null;

    while (*pp != NULL) {
        if (*(unsigned int*)*pp == id) {
            return *pp;
        }
        ++pp;
    }

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null ==NULL) {
        return NULL;
    }

    user_t** pp = users_or_null;

    while (*pp != NULL) {
        const char* name = (const char*)*pp + 4;
        if (!strcmp(name, username)) {
            return *pp;
        }
        ++pp;
    }

    return NULL;
}

    

int update_email(user_t** users_or_null, unsigned int id, const char* email)
{
    if (users_or_null == NULL) {
        return FALSE;
    }

    user_t* user = get_user_by_id_or_null(users_or_null, id);
    
    if (user == NULL) {
        return FALSE;
    }
    
    FILE* stream;
    stream = fopen("log.txt", "a");
    if (stream == NULL) {
        return FALSE;
    }

    char old_email[51];
    strcpy(old_email, user->email);
    char new_email[51];
    strcpy(new_email, email);

    strcpy(user->email, email);

#ifdef RELEASE
    
    convert_str_to_release_mode(old_email, '@');
    convert_str_to_release_mode(new_email, '@');

#endif

    fprintf(stream, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", id, old_email, new_email);

    fclose(stream);

    return TRUE;
}

int update_password(user_t** users_or_null, unsigned int id, const char* password)
{
    if (users_or_null == NULL) {
        return FALSE;
    }

    user_t* user = get_user_by_id_or_null(users_or_null, id);
    
    if (user == NULL) {
        return FALSE;
    }
    
    FILE* stream;
    stream = fopen("log.txt", "a");
    if (stream == NULL) {
        return FALSE;
    }

    char old_password[51];
    strcpy(old_password, user->password);
    char new_password[51];
    strcpy(new_password, password);

    strcpy(user->password, password);

#ifdef RELEASE
    
    convert_str_to_release_mode(old_password, '\0');
    convert_str_to_release_mode(new_password, '\0');

#endif

    fprintf(stream, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", id, old_password, new_password);

    fclose(stream);

    return TRUE;
}

void convert_str_to_hide_mode(char* str, char mark)
{
    char first_letter = *str;
    
    char* p = str;
    char* p_next = str + 1;

    while (*p_next != mark) {
        *p++ = '*';
        ++p_next;
    }

    if (p == str) {
        *str = '*';
        return;
    } else {
        *str = first_letter;
    }

    *(str + 1) = '*';
}


        



