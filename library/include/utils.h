//
// Created by wojciech on 01/08/2021.
//

#ifndef CINEMA_UTILS_H
#define CINEMA_UTILS_H

#include "vector"
#include "functional"

namespace Utils{
    Sudoku solveSudoku(const Sudoku& sudoku);
    std::vector<std::vector<CellPos>> getSimpleConstraints();
    std::function<bool(const std::vector<CellPtr>&, int)> getSumConstraints(int expectedSum);
}

#endif //CINEMA_UTILS_H
