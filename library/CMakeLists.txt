cmake_minimum_required(VERSION 3.19)
project(SudokuLibrary VERSION 0.0.1)

set(SOURCE_FILES src/Sudoku.cpp ../test/master.cpp src/Cell.cpp include/Cell.h ../test/CellTest.cpp include/typedefs.h src/utils.cpp include/utils.h ../test/SudokuTest.cpp)
add_library(SudokuLibrary ${SOURCE_FILES})

set_target_properties(SudokuLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLibrary PUBLIC include)
