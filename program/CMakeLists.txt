cmake_minimum_required(VERSION 3.19)

project(Program)
find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS ../library REQUIRED)
set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES src/main.cpp
        # only for debugging
        ../library/src/Sudoku.cpp
        ../library/src/Cell.cpp
        ../library/src/CellGroup.cpp
        ../library/src/utils.cpp
        ../library/src/CellUniqueGroup.cpp
        ../library/include/Cell.h
        ../library/include/CellGroup.h
        ../library/include/typedefs.h
        ../library/include/utils.h
        ../library/include/CellUniqueGroup.h
        ../library/src/Row.cpp
        ../library/include/Row.h
        ../library/src/Column.cpp
        ../library/include/Column.h
        ../library/src/SquareBox.cpp
        ../library/include/SquareBox.h
        ../library/include/CustomConstraintCellGroup.h
        ../library/src/CustomConstraintCellGroup.cpp)

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program debug ${SUDOKU_LIBRARY})
target_include_directories(Program PUBLIC
        include
        ../library/include
        )


