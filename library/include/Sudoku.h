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
    std::vector<std::vector<std::string>> verticalBoarders;

    const std::string verticalSeparator = "\u2502";
    const std::string leftUpperCorner = "\u250C";
    const std::string leftLowerCorner = "\u2514";
    const std::string rightUpperCorner = "\u2510";
    const std::string rightLowerCorner = "\u2518";
    const std::string horizontalBar = "\u2500\u2500\u2500";
    const std::string upperJunction = "\u252C";
    const std::string lowerJunction = "\u2534";

    void fillWithPossibleNumbers();
    void initializeBoarders();
    int getFlattenedCoord(int row, int col) const;
    int getFlattenedIndex(int row, int col) const;
    std::string getUpperHorizontalLine() const;
    std::string getLowerHorizontalLine() const;
    bool isNumPosValid(NumPosition num) const;
    std::vector<CellPtr> getCellsFromConstraints(CellPos cellPos) const;
    std::vector<CellPtr> getCellsFromColumn(CellPos cellPos) const;
    std::vector<CellPtr> getCellsFromRow(CellPos cellPos) const;
public:
    Sudoku(std::vector<NumPosition>, std::vector<std::vector<CellPos>> constraints);
    std::string getBoardString() const;
    bool isNumAllowed(NumPosition numPosition) const;
    bool isSolved() const;
    void solve();
};


#endif //SUDOKULOGIC_SUDOKU_H
