cmake_minimum_required(VERSION 3.19)

project(Program)
find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS ../library REQUIRED)
set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES src/main.cpp
        # only for debugging
        ../library/src/GameComponents/Sudoku.cpp
        ../library/src/utils.cpp
        ../library/include/typedefs.h
        ../library/include/utils.h
        )

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program debug ${SUDOKU_LIBRARY})
target_include_directories(Program PUBLIC
        include
        ../library/include
        )


