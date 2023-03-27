#ifndef USER_H
#define USER_H

typedef struct user {
    unsigned int id;
    char username[51];
    char unused1;
    char email[51];
    char unused2;
    char password[51];
    char unused3;
} user_t;

#endif /* USER_H */


