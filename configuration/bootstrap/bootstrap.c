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

    status = fileExists(CREDENTIALS_DATABASE);

    if (!status) {
        fp = fopen(CREDENTIALS_DATABASE, "wb");

        if (fp != NULL) {
            strncpy(credentials.password, defaultPassword,
                    sizeof(defaultPassword));
            strncpy(credentials.username, defaultUsername,
                    sizeof(defaultUsername));
            fwrite(&credentials, CREDENTIALS_FILE_SIZE, 1, fp);
            fclose(fp);
        }
    }

    status = fileExists(LIBRARY_DATABASE);

    if (!status) {
        fp = fopen(LIBRARY_DATABASE, "wb");
        fclose(fp);
    }
}
