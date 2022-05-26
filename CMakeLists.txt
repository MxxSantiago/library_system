cmake_minimum_required(VERSION 3.21)
project(library_system C)

set(CMAKE_C_STANDARD 99)

add_executable(library_system main.c configuration/structure.h configuration/constants.h source/helpers/isDateValid/isDateValid.c source/helpers/isDateValid/isDateValid.h source/helpers/isNameValid/isNameValid.c source/helpers/isNameValid/isNameValid.h source/helpers/fileExists/fileExists.c source/helpers/fileExists/fileExists.h source/style/alignToCenter/alignToCenter.c source/style/alignToCenter/alignToCenter.h source/style/header/header.c source/style/header/header.h configuration/bootstrap/bootstrap.c configuration/bootstrap/bootstrap.h source/auth/login/login.c source/auth/login/login.h source/app.c source/app.h)
