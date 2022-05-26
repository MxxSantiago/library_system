#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../configuration/structure.h"
#include "../../style/header/header.h"
#include "../../app.h"

void login() {
    int attempts = 0;
    FILE *fp = NULL;
    Credentials credentials;
    unsigned char password[PASSWORD_LENGTH];
    unsigned char username[USERNAME_LENGTH];

    header("Login");

    fp = fopen(DATABASE, "rb");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    fread(&credentials, FILE_SIZE, 1, fp);
    fclose(fp);

    do {
        printf("Username:");
        fgets(username, USERNAME_LENGTH, stdin);

        printf("\nPassword:");
        fgets(password, PASSWORD_LENGTH, stdin);

        if ((!strcmp(username, credentials.username)) &&
            (!strcmp(password, credentials.password))) {
            menu();
        } else {
            printf("A user with this username and password does not exist");
            attempts++;
        }

    } while (attempts <= 3);
    if (attempts > 3) {
        header("Login Failed");
        printf("You have made too many attempts, the application will close\n\n");
        system("pause");
        system("cls");
    }
}