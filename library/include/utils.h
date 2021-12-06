//
// Created by wojciech on 01/08/2021.
//

#ifndef CINEMA_UTILS_H
#define CINEMA_UTILS_H

#include "vector"
#include "functional"
#include "CellGroup.h"

namespace Utils{
    /**
     * Self-explanatory
     * @param sudoku a reference to a Sudoku object
     * @return a solved Sudoku object
     */
    Sudoku solveSudoku(const Sudoku& sudoku);
    /**
     * Given a vector of 81 cells returns CellGroups for a traditional sudoku
     * @throws invalid_exception if the number of cells ≠ 81
     * @param cells a vector of shared pointers to cells
     * @return a vector of shared pointers to cell groups
     */
    std::vector<CellVerifiers::CellGroup::SharedPtr> getSimpleGroup(const std::vector<CellPtr>& cells);
    /**
     * Returns a predicate which is true if a vector of Cells sums up to expectedSum
     * @param expectedSum
     * @return A predicate taking a vector of shared pointers to cells and returns a bool value
     */
    std::function<bool(const std::vector<CellPtr>&, int)> getSumConstraints(int expectedSum);
    /**
     * Takes an array of tuples (row, column, number) and build a vector of cells of pointers.
     * @throws invalid_exception if at least one cell is over-defined (two numPositions pointing to
     * the same cell in the board) or row is not in range [1, 9] or col is not in range [1, 9]
     * or number is not in range [1, 9]
     * @param numPositions
     * @return A vector of shared pointers to cells of length 81
     */
    std::vector<CellPtr> getCellsFromNumPoses(const std::vector<NumPosition>& numPositions);
}

#endif //CINEMA_UTILS_H
