#include <string.h>
#include <ctype.h>

int isNameValid(const char *name) {
    int validName = 1, nameLength, index;

    nameLength = strlen(name);

    for (index = 0; index < nameLength; ++index) {
        if (!(isalpha(name[index])) && (name[index] != '\n') &&
            (name[index] != ' ')) {
            validName = 0;
            break;
        }
    }

    return validName;
}