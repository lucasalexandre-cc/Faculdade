cmake_minimum_required(VERSION 3.7)
project(T05)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES cliente.h cliente.c encadeamento_interior.h encadeamento_interior.c lista_clientes.h
        lista_clientes.c ufftest.h test_encadeamento_interior.c)
add_executable(T05 ${SOURCE_FILES})