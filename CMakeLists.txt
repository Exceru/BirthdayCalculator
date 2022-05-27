cmake_minimum_required(VERSION 3.22)
project(geburtstagsuebung C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -Wextra -pedantic")


add_executable(geburtstagsuebung geburtstag.c)
