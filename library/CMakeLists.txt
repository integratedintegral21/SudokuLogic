cmake_minimum_required(VERSION 3.4)
project(SudokuLogicLibrary VERSION 0.2.0)

set(SOURCE_FILES
        src/Sudoku.cpp
        src/Cell.cpp
        include/Cell.h
        include/typedefs.h
        src/utils.cpp
        include/utils.h
        )
add_library(SudokuLogicLibrary ${SOURCE_FILES})

set_target_properties(SudokuLogicLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLogicLibrary PUBLIC include)
