cmake_minimum_required(VERSION 4.3)
project(Terminal_Tower_Defense C)

set(CMAKE_C_STANDARD 11)

add_executable(Terminal_Tower_Defense
        src/main.c
        src/mapa.c
        src/mapa.h
)
