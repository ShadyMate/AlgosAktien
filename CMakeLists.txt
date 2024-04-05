cmake_minimum_required(VERSION 3.27)
project(AlgosAktien)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(AlgosAktien
        include/Hash.h
        include/Stock.h
        src/Hash.cpp
        src/Stock.cpp
        main.cpp)
