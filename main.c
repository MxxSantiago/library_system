#include "configuration/bootstrap/bootstrap.h"

#include "source/auth/login/login.h"

int main() {
    bootstrap();
    login();
    return 0;
}

