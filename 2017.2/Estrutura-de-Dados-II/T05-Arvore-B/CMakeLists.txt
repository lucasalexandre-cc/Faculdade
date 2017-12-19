cmake_minimum_required(VERSION 3.7)
project(Arvore_B)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES arvore_b.c arvore_b.h cliente.c cliente.h lista_clientes.c lista_clientes.h
        lista_nos.c lista_nos.h metadados.c metadados.h no.c no.h test_arvore_b.c ufftest.h)
add_executable(Arvore_B ${SOURCE_FILES})