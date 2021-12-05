//
// Created by wojciech on 01/08/2021.
//

#ifndef CINEMA_UTILS_H
#define CINEMA_UTILS_H

#include "vector"
#include "functional"
#include "CellGroup.h"

namespace Utils{
    Sudoku solveSudoku(const Sudoku& sudoku);
    std::vector<CellVerifiers::CellGroup::SharedPtr> getSimpleGroup(const std::vector<CellPtr>& cells);
    std::function<bool(const std::vector<CellPtr>&, int)> getSumConstraints(int expectedSum);
}

#endif //CINEMA_UTILS_H
