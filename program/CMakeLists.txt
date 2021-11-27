cmake_minimum_required(VERSION 3.19)

project(Program)
find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS ../library REQUIRED)

set(SOURCE_FILES src/main.cpp)

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program ${SUDOKU_LIBRARY})
target_include_directories(Program PUBLIC
        include
        ../library/include
        )


