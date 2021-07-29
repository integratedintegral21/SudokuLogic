//
// Created by wojciech on 28/07/2021.
//

#ifndef SUDOKULOGIC_SUDOKU_H
#define SUDOKULOGIC_SUDOKU_H

#include <vector>
#include <string>
#include "typedefs.h"

class Sudoku {
private:
    // flattened 9x9 board
    std::vector<CellPtr> board;
    // list of lists of cells where all numbers are unique
    std::vector<std::vector<CellPos>> constraints;
    // list containing cell separators
    std::vector<std::vector<std::string>> horizontalBoarders;
    std::vector<std::vector<std::string>> verticalBoarders;

    const std::string verticalSeparator = "\u2502";
    const std::string horizontalSeparator = "\u250C\u2500\u2510";
    const std::string verticalHighlightSeparator = "\u001b[33m" + verticalSeparator + "\u001b[0m";
    const std::string horizontalHighlightSeparator = "\u001b[33m" + horizontalSeparator + "\u001b[0m";

    void fillWithPossibleNumbers();
    void initializeBoarders();
    int getFlattenedCoord(int row, int col) const;
    int getFlattenedIndex(int row, int col) const;
    std::string getUpperHorizontalLine(bool isHighlighted) const;
    std::string getLowerHorizontalLine(bool isHighlighted) const;
public:
    Sudoku(std::vector<NumPosition>, std::vector<std::vector<CellPos>> constraints);
    std::string getBoardString() const;
    bool isNumAllowed(NumPosition numPosition) const;
    bool isSolved() const;
    void solve();
};


#endif //SUDOKULOGIC_SUDOKU_H
