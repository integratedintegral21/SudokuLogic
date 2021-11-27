cmake_minimum_required(VERSION 3.4)
project(SudokuLogicLibrary VERSION 0.2.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        src/Sudoku.cpp
        src/Cell.cpp
        src/CellGroup.cpp
        src/utils.cpp
        src/CellUniqueGroup.cpp
        include/Cell.h
        include/CellGroup.h
        include/typedefs.h
        include/utils.h
        include/CellUniqueGroup.h
        src/Row.cpp
        include/Row.h
        src/Column.cpp
        include/Column.h
        src/SquareBox.cpp
        include/SquareBox.h
        src/CustomConstraintCellGroup.cpp
        include/CustomConstraintCellGroup.h)
add_library(SudokuLogicLibrary SHARED ${SOURCE_FILES})
target_link_libraries(SudokuLogicLibrary PUBLIC Threads::Threads)

set_target_properties(SudokuLogicLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLogicLibrary PUBLIC include)
