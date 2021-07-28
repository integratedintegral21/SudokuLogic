cmake_minimum_required(VERSION 3.19)

project(Program)

set(SOURCE_FILES src/main.cpp
        ../library/include/Sudoku.h
        ../library/src/Sudoku.cpp ../library/include/Cell.cpp ../library/include/Cell.h ../library/include/typedefs.h)

add_executable(Program ${SOURCE_FILES})
include_directories(
        ../library/include
)

target_include_directories(Program PUBLIC include)


