cmake_minimum_required(VERSION 3.7)
project(T03)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES test_intercalacao.c intercalacao.c intercalacao.h cliente.c cliente.h lista_clientes.c lista_clientes.h arvore.c arvore.h)
add_executable(T03 ${SOURCE_FILES})

target_link_libraries(T03 m)