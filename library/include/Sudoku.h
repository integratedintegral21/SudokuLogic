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
    // list of lists of cells where all numbers are unique
    std::vector<std::vector<CellPos>> constraints;
    void fillWithPossibleNumbers();
    int getFlattenedCoord(int row, int col) const;
    int getFlattenedIndex(int row, int col) const;
public:
    Sudoku(std::vector<NumPosition>, std::vector<std::vector<CellPos>> constraints);
    std::string to_string() const;
    bool isNumAllowed(NumPosition numPosition) const;
    bool isSolved() const;
    void solve();
};


#endif //SUDOKULOGIC_SUDOKU_H
