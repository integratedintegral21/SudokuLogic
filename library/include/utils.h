//
// Created by wojciech on 01/08/2021.
//

#ifndef CINEMA_UTILS_H
#define CINEMA_UTILS_H

#include "vector"
#include "functional"
#include "CellVerifiers/CellGroupObserver.h"
#include "GameComponents/Cell.h"
#include "typedefs.h"

namespace Utils{
    /**
     * Self-explanatory
     * @param sudoku a reference to a Sudoku object
     * @return a solved Sudoku object
     */
    // GameComponents::Sudoku solveSudoku(const GameComponents::Sudoku& sudoku);
    /**
     * Takes a list of empty cells and adds appropriate groups such they from a simple sudoku board
     * @param cells a vector of shared pointers to Cell objects
     * @throw invalid_argument if number of cells is not 81 or not all cells are unique in groups
     * @return a vector of shared pointers to cells with groups assigned
     */
    std::vector<GameComponents::Cell::SharedPtr> getSimpleSudokuCells(const std::vector<GameComponents::Cell::SharedPtr>& cells);
    /**
     * Takes an array of tuples (row, column, number) and build a vector of cells of pointers.
     * @throws invalid_exception if at least one cell is over-defined (two numPositions pointing to
     * the same cell in the board) or row is not in range [1, 9] or col is not in range [1, 9]
     * or number is not in range [1, 9]
     * @param numPositions
     * @return A vector of shared pointers to cells of length 81
     */
    std::vector<GameComponents::Cell::SharedPtr> getCellsFromNumPoses(const std::vector<NumPosition>& numPositions);
}

#endif //CINEMA_UTILS_H
