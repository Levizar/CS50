cmake_minimum_required(VERSION 3.16)
project(CS50 C)

set(CMAKE_C_STANDARD 11)

add_executable(CS50
        pset1/hello/hello.c
        pset1/credit/credit.c
        pset1/mario/mario.c
        pset2/substitution/substitution.c
        pset2/readability/readabilty.c
        pset3/plurality/plurality.c
        pset3/tideman/tideman.c)
