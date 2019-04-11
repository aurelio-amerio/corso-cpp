cmake_minimum_required(VERSION 3.7)
project(corso_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(corso_cpp
        main.cpp)

#lezione 1
add_executable(lezione1_corso
        lezione1/lezione.cpp)
#esercizi
#1
add_executable(lezione1_es1
        lezione1/es1.cpp)
#2
add_executable(lezione1_es2
        lezione1/es2.cpp)

