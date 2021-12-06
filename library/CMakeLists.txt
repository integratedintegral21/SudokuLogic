cmake_minimum_required(VERSION 3.4)
project(SudokuLogicLibrary VERSION 0.2.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        src/GameComponents/Sudoku.cpp
        src/GameComponents/Cell.cpp
        src/CellVerifiers/CellGroup.cpp
        src/utils.cpp
        src/CellVerifiers/CellUniqueGroup.cpp
        include/GameComponents/Cell.h
        include/CellVerifiers/CellGroup.h
        include/typedefs.h
        include/utils.h
        include/CellVerifiers/CellUniqueGroup.h
        src/CellVerifiers/Row.cpp
        include/CellVerifiers/Row.h
        src/CellVerifiers/Column.cpp
        include/CellVerifiers/Column.h
        src/CellVerifiers/SquareBox.cpp
        include/CellVerifiers/SquareBox.h
        src/CellVerifiers/CustomConstraintCellGroup.cpp
        include/CellVerifiers/CustomConstraintCellGroup.h)
add_library(SudokuLogicLibrary SHARED ${SOURCE_FILES})
target_link_libraries(SudokuLogicLibrary PUBLIC Threads::Threads)

set_target_properties(SudokuLogicLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLogicLibrary PUBLIC include)
