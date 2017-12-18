cmake_minimum_required(VERSION 3.9)
project(xorcipher)

set(CMAKE_CXX_STANDARD 11)

add_executable(xorcipher
        c_validate.c
        c_validate.h
        checkascii.c
        checkascii.h
        cipher.c
        cipher.h
        dict_analysis.c
        dict_analysis.h
        freq_analysis.c
        freq_analysis.h
        main.c
        options.c
        options.h
        read_file.c
        read_file.h)
