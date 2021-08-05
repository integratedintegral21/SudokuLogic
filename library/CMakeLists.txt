cmake_minimum_required(VERSION 3.4)
project(SudokuLibrary VERSION 0.0.1)

set(SOURCE_FILES
        src/Sudoku.cpp
        src/Cell.cpp
        include/Cell.h
        include/typedefs.h
        src/utils.cpp
        include/utils.h
        )
add_library(SudokuLibrary STATIC SHARED ${SOURCE_FILES})

set_target_properties(SudokuLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLibrary PUBLIC include)
