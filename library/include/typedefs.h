//
// Created by wojciech on 28/07/2021.
//

#ifndef CINEMA_TYPEDEFS_H
#define CINEMA_TYPEDEFS_H

#include "memory"

class Cell;
class Sudoku;

typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Sudoku> SudokuPtr;

// (row, col, number)
typedef std::tuple<int, int, int> NumPosition;
// (row, col)
typedef std::tuple<int, int> CellPos;

#endif //CINEMA_TYPEDEFS_H
