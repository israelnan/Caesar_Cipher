cmake_minimum_required(VERSION 3.23)
project(Caesar Cipher C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Caesar Cipher
        cipher.h
        cipher.c
        tests.h
        tests.c
        main.c)
