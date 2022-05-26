#include "../../../configuration/structure.h"

int isDateValid(Date *date) {
    if (date->year > 2022 ||
        date->year < 1) {
        return 0;
    }

    if (date->month < 1 || date->month > 12) {
        return 0;
    }

    if (date->day < 1 || date->day > 31) {
        return 0;
    }

    if (date->month == 2) {
        if ((((date->year % 4 == 0) &&
              (date->year % 100 != 0)) ||
             (date->year % 400 == 0))) {
            return (date->day <= 29);
        } else {
            return (date->day <= 28);
        }
    }

    if (date->month == 4 || date->month == 6 ||
        date->month == 9 || date->month == 11) {
        return (date->day <= 30);
    }

    return 1;
}