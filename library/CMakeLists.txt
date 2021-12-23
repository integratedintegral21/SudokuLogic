cmake_minimum_required(VERSION 3.4)
project(SudokuLogicLibrary VERSION 2.0.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        src/utils.cpp
        include/typedefs.h
        include/utils.h
        include/GameComponents/GameComponents.h
        src/GameComponents/Cell.cpp include/GameComponents/Cell.h
        include/CellVerifiers/CellVerifiers.h
        src/CellVerifiers/CellGroupObserver.cpp
        include/CellVerifiers/CellGroupObserver.h
        src/CellVerifiers/UniqueCellGroup.cpp
        include/CellVerifiers/UniqueCellGroup.h
        src/CellVerifiers/AggregatedCellGroup.cpp
        include/CellVerifiers/AggregatedCellGroup.h
        src/CellVerifiers/IntegerSumCellGroup.cpp
        include/CellVerifiers/UnsignedIntegerSumCellGroup.h
        src/GameComponents/Sudoku.cpp
        include/GameComponents/Sudoku.h include/SudokuSolvers/Solvers.h src/SudokuSolvers/SudokuSolver.cpp include/SudokuSolvers/SudokuSolver.h src/SudokuSolvers/SingleThreadBacktrackingSolver.cpp include/SudokuSolvers/SingleThreadBacktrackingSolver.h src/SudokuSolvers/MultiThreadBacktrackingSolver.cpp include/SudokuSolvers/MultiThreadBacktrackingSolver.h)
add_library(SudokuLogicLibrary SHARED ${SOURCE_FILES})
target_link_libraries(SudokuLogicLibrary PUBLIC Threads::Threads)

set_target_properties(SudokuLogicLibrary PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(SudokuLogicLibrary PUBLIC include)
