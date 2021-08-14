//
// Created by wojciech on 01/08/2021.
//

#ifndef CINEMA_UTILS_H
#define CINEMA_UTILS_H

#include "vector"

Sudoku solveSudoku(const Sudoku& sudoku);
std::vector<std::vector<CellPos>> getSimpleConstraints();

#endif //CINEMA_UTILS_H
