//
// Created by wojciech on 28/07/2021.
//

#ifndef SUDOKULOGIC_SUDOKU_H
#define SUDOKULOGIC_SUDOKU_H

#include <vector>
#include "typedefs.h"

class Sudoku {
private:
    // flattened 9x9 board
    std::vector<CellPtr> board;
    // list of numbers of cells where all numbers are unique
    std::vector<std::vector<int>> constraints;
};


#endif //SUDOKULOGIC_SUDOKU_H
