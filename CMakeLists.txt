cmake_minimum_required(VERSION 4.1)
project(aoc C)

set(CMAKE_C_STANDARD 11)

#file(GLOB_RECURSE SHARED src/shared/*.c)

add_executable(day01 src/day_01.c)
add_executable(day02 src/day_02.c)
add_executable(day03 src/day_03.c)
add_executable(day04 src/day_04.c)
