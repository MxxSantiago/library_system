#include <stdio.h>

int fileExists(const char *path) {
    int status = 0;
    FILE *fp = fopen(path, "rb");

    if (fp != NULL) {
        status = 1;
        fclose(fp);
    }

    return status;
}