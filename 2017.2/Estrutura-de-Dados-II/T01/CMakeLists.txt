cmake_minimum_required(VERSION 3.7)
project(T01)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c agencia.c conta_corrente.c conta_corrente.h agencia.h)
add_executable(T01 ${SOURCE_FILES})