//
// Created by wojciech on 28/07/2021.
//

#ifndef CINEMA_TYPEDEFS_H
#define CINEMA_TYPEDEFS_H

#include "memory"

class Cell;

typedef std::shared_ptr<Cell> CellPtr;

// (row, col, number)
typedef std::tuple<int, int, int> NumPosition;
typedef std::tuple<int, int> CellPos;

#endif //CINEMA_TYPEDEFS_H
