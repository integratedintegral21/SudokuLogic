cmake_minimum_required(VERSION 3.4)
project(SudokuLogicLibrary VERSION 1.0.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        src/GameComponents/Sudoku.cpp
        src/utils.cpp
        include/typedefs.h
        include/utils.h
        )
add_library(SudokuLogicLibrary SHARED ${SOURCE_FILES})
target_link_libraries(SudokuLogicLibrary PUBLIC Threads::Threads)

set_target_properties(SudokuLogicLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLogicLibrary PUBLIC include)
