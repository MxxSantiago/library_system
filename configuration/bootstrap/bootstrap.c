#include <stdio.h>
#include <string.h>

#include "../structure.h"

#include "../../source/helpers/fileExists/fileExists.h"

void bootstrap() {
    int status;
    FILE *fp = NULL;
    Credentials credentials;
    const char defaultUsername[] = "admin\n";
    const char defaultPassword[] = "123\n";

    status = fileExists(DATABASE);

    if (!status) {
        fp = fopen(DATABASE, "wb");

        if (fp != NULL) {
            strncpy(credentials.password, defaultPassword,
                    sizeof(defaultPassword));
            strncpy(credentials.username, defaultUsername,
                    sizeof(defaultUsername));
            fwrite(&credentials, FILE_SIZE, 1, fp);
            fclose(fp);
        }
    }
}