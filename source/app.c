#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../configuration/structure.h"

#include "style/header/header.h"

#include "helpers/isNameValid/isNameValid.h"
#include "helpers/isDateValid/isDateValid.h"

void create() {
    FILE *fp = NULL;
    Book book;
    int status;
    unsigned int enteredID, flag = 0;

    header("Create Or Add A Book");

    while (!flag) {
        fp = fopen(DATABASE, "rb");

        if (fp == NULL) {
            printf("File is not opened\n");
            exit(1);
        }

        if (fseek(fp, FILE_SIZE, SEEK_SET) != 0) {
            fclose(fp);
            printf("\nAn error occurred while reading the file\n");
            exit(1);
        }

        flag = 1;

        printf("Book ID: ");
        scanf("%u", &enteredID);

        while (fread(&book, sizeof(book), 1,
                     fp)) {
            if (book.id == enteredID) {
                printf("\nThe entered ID is already in use, enter another one\n\n");
                flag = 0;
            }
        }

        if (flag) book.id = enteredID;
    }

    fp = fopen(DATABASE, "ab+");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    do {
        printf("\nBook Name: ");
        fflush(stdin);
        fgets(book.name, BOOK_NAME_LENGTH, stdin);

        status = isNameValid(book.name);

        if (!status) {
            printf("\nInvalid input, try again");
        }
    } while (!status);
    do {
        printf("\nAuthor Name: ");
        fflush(stdin);
        fgets(book.author, AUTHOR_LENGTH, stdin);

        status = isNameValid(book.author);

        if (!status) {
            printf("\nName contain invalid character. Please enter again.");
        }
    } while (!status);
    do {
        printf("\nClient Name: ");
        fflush(stdin);
        fgets(book.client, CLIENT_LENGTH, stdin);

        status = isNameValid(book.client);

        if (!status) {
            printf("\nInvalid input, try again");
        }
    } while (!status);
    do {
        printf("\nEnter date in format (day/month/year): ");
        scanf("%d/%d/%d", &book.issueDate.day,
              &book.issueDate.month,
              &book.issueDate.year);

        status = isDateValid(&book.issueDate);

        if (!status) printf("\nInvalid input, enter a valid date.\n");
    } while (!status);

    fwrite(&book, sizeof(book), 1, fp);
    fclose(fp);
}

void search() {
    int found = 0;
    char bookName[BOOK_NAME_LENGTH];
    FILE *fp = NULL;
    Book book;

    fp = fopen(DATABASE, "rb");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    header("Search books");

    if (fseek(fp, FILE_SIZE, SEEK_SET) != 0) {
        fclose(fp);
        printf("\nAn error occurred while reading the file\n");
        exit(1);
    }

    printf("Enter Book Name to search:");
    fflush(stdin);
    fgets(bookName, BOOK_NAME_LENGTH, stdin);

    while (fread(&book, sizeof(book), 1,
                 fp)) {
        if (!strcmp(book.name, bookName)) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\nBook id = %u\n", book.id);
        printf("Book name = %s", book.name);
        printf("Book author = %s", book.author);
        printf("Book issue =  (%d/%d/%d)",
               book.issueDate.day,
               book.issueDate.month,
               book.issueDate.year);
    } else {
        printf("\nNo Record");
    }

    fclose(fp);
    printf("\n\n");
    system("pause");
}

void print() {
    int cantity = 0;
    FILE *fp = NULL;
    Book book;

    header("Print Books");

    fp = fopen(DATABASE, "rb");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    if (fseek(fp, FILE_SIZE, SEEK_SET) != 0) {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }

    while (fread(&book, sizeof(book), 1,
                 fp)) {
        printf("Book id = %u", book.id);
        printf("\nBook name = %s", book.name);
        printf("Book author = %s", book.author);
        printf("Book issue =  (%d/%d/%d)\n\n",
               book.issueDate.day,
               book.issueDate.month,
               book.issueDate.year);

        cantity = 1;
    }

    fclose(fp);

    if (!cantity) {
        printf("There are no books to print");
    }

    printf("\n\n");
    system("pause");
}

void delete() {
    int found = 0, searchedBook = 0;
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    Credentials credentials;
    Book book;

    header("Delete Book");

    fp = fopen(DATABASE, "rb");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    tmpFp = fopen("tmp.bin", "wb");

    if (tmpFp == NULL) {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }

    fread(&credentials, FILE_SIZE, 1, fp);
    fwrite(&credentials, FILE_SIZE, 1, tmpFp);

    printf("Book ID:");
    scanf("%i", &searchedBook);

    while (fread(&book, sizeof(book), 1,
                 fp)) {
        if (book.id != searchedBook) {
            fwrite(&book, sizeof(book), 1,
                   tmpFp);
        } else {
            found = 1;
        }
    }

    (found) ? printf("\nBook deleted") : printf(
            "\nBook ID not found");

    printf("\n\n");
    system("pause");

    fclose(fp);
    fclose(tmpFp);
    remove(DATABASE);
    rename("tmp.bin", DATABASE);
}

void updateCredentials(void) {
    FILE *fp = NULL;
    Credentials credentials;
    unsigned char password[PASSWORD_LENGTH];
    unsigned char username[USERNAME_LENGTH];

    header("Update Credentials");

    fp = fopen(DATABASE, "rb+");

    if (fp == NULL) {
        printf("File is not opened\n");
        exit(1);
    }

    fread(&credentials, FILE_SIZE, 1, fp);

    if (fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        printf("Facing issue while updating password\n");
        exit(1);
    }

    printf("New Username:");
    fflush(stdin);
    fgets(username, USERNAME_LENGTH, stdin);

    printf("\n\nNew Password:");
    fflush(stdin);
    fgets(password, PASSWORD_LENGTH, stdin);

    strncpy(credentials.username, username, sizeof(username));
    strncpy(credentials.password, password, sizeof(password));

    fwrite(&credentials, FILE_SIZE, 1, fp);
    fclose(fp);

    system("cls");
    header("Update Credential");
    printf("Credentials changed successfully, the application will close, log in with your new credentials\n\n");
    system("pause");

    exit(1);
}

void menu() {
    int option = 0;

    do {
        header("Menu");

        printf("1. Create/Add");
        printf("\n2. Search");
        printf("\n3. Print");
        printf("\n4. Delete");
        printf("\n5. Update Password");
        printf("\n6. Exit");

        printf("\n\nOption: ");
        scanf("%i", &option);

        switch (option) {
            case 1:
                create();
                break;
            case 2:
                search();
                break;
            case 3:
                print();
                break;
            case 4:
                delete();
                break;
            case 5:
                updateCredentials();
                break;
            case 6:
                exit(1);
            default:
                printf("Invalid input");
                break;
        }
    } while (option != 0);
}

