cmake_minimum_required(VERSION 3.19)

project(Program)
find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS ../library REQUIRED)
set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES src/main.cpp
        # only for debugging
        ../library/src/GameComponents/Sudoku.cpp
        ../library/src/GameComponents/Cell.cpp
        ../library/src/CellVerifiers/CellGroup.cpp
        ../library/src/utils.cpp
        ../library/src/CellVerifiers/CellUniqueGroup.cpp
        ../library/include/GameComponents/Cell.h
        ../library/include/CellVerifiers/CellGroup.h
        ../library/include/typedefs.h
        ../library/include/utils.h
        ../library/include/CellVerifiers/CellUniqueGroup.h
        ../library/src/CellVerifiers/Row.cpp
        ../library/include/CellVerifiers/Row.h
        ../library/src/CellVerifiers/Column.cpp
        ../library/include/CellVerifiers/Column.h
        ../library/src/CellVerifiers/SquareBox.cpp
        ../library/include/CellVerifiers/SquareBox.h
        ../library/include/CellVerifiers/CustomConstraintCellGroup.h
        ../library/src/CellVerifiers/CustomConstraintCellGroup.cpp)

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program debug ${SUDOKU_LIBRARY})
target_include_directories(Program PUBLIC
        include
        ../library/include
        )


