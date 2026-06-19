cmake_minimum_required(VERSION 4.2)
project(petshop_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(petshop_C
        include/servico.h
        include/consulta.h
        src/servico.c
        src/consulta.c
        main.c)
