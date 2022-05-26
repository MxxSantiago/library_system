#include <stdlib.h>
#include <stdio.h>

#include "../alignToCenter/alignToCenter.h"

void header(const char *message) {
    system("cls");
    printf("===========================================================================");
    printf("\n\n                          Library Management System                      \n");
    printf("\n===========================================================================\n");
    alignToCenter(message);
    printf("\n===========================================================================\n\n\n");
}