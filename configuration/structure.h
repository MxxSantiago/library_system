#ifndef UNTITLED7_STRUCTURE_H

#include "constants.h"

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} Credentials;

typedef struct {
    unsigned int books_id;
    char name[BOOK_NAME_LENGTH];
    char author[AUTHOR_LENGTH];
    char client[CLIENT_LENGTH];
    Date bookIssueDate;
} Book;

#define UNTITLED7_STRUCTURE_H

#endif
