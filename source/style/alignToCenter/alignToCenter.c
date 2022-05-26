#include <string.h>
#include <stdio.h>

void alignToCenter(const char *message) {
    int len, position;

    len = (78 - strlen(message)) / 2;

    for (position = 0; position < len; position++) printf(" ");

    printf("%s", message);
}