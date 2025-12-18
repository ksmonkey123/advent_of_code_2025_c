cmake_minimum_required(VERSION 4.1)
project(aoc C)

set(CMAKE_C_STANDARD 11)

#file(GLOB_RECURSE SHARED src/shared/*.c)

add_executable(day01 src/day_01.c)
add_executable(day02 src/day_02.c)
add_executable(day03 src/day_03.c)
add_executable(day04 src/day_04.c)
add_executable(day05 src/day_05/main.c src/day_05/model.c src/day_05/part1.c src/day_05/part2.c src/day_05/util.c)
add_executable(day06 src/day_06.c
        src/utils/chargrid.c
        src/utils/chargrid.h)