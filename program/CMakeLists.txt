cmake_minimum_required(VERSION 3.19)

project(Program)

set(SOURCE_FILES src/main.cpp)

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program SudokuLibrary)
target_include_directories(Program PUBLIC include)


