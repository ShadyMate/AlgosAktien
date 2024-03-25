cmake_minimum_required(VERSION 3.27)
project(AlgosAktien)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgosAktien main.cpp
        yahoo_finance.cpp
        yahoo_finance.h)
