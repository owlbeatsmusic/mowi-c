#!/bin/zsh

gcc -Wall -pedantic -std=iso9899:1999 \
    -I./include -I./lib \
    \
    src/main.c \
    src/mowi/mowi.c \
    \
    -o \
    main
