cmake_minimum_required(VERSION 3.7)
project(T02)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES test_geracao_particoes.c cliente.c geracao_particoes.c lista_clientes.c nomes.c)
add_executable(T02 ${SOURCE_FILES})