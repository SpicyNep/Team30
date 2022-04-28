cmake_minimum_required(VERSION 3.7.2)
project(BSPrak C)

set(CMAKE_C_STANDARD 99)

add_executable(BSPrak main.c keyValStore.c keyValStore.h main.h sub.c sub.h)
