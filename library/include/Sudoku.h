//
// Created by wojciech on 28/07/2021.
//

#ifndef SUDOKULOGIC_SUDOKU_H
#define SUDOKULOGIC_SUDOKU_H

#include <vector>
#include <string>
#include <map>
#include "typedefs.h"

class Sudoku {
private:
    // flattened 9x9 board
    std::vector<CellPtr> board;
    // list of lists of cells where all numbers are unique
    std::vector<std::vector<CellPos>> constraints;
    // assigns constrained cells to every Cell
    std::map<CellPtr, std::vector<CellPtr>> constraintsMap;
    // list containing cell separators
    std::vector<std::vector<std::string>> verticalBoarders;

    const std::string verticalSeparator = "\u2502";
    const std::string leftUpperCorner = "\u250C";
    const std::string leftLowerCorner = "\u2514";
    const std::string rightUpperCorner = "\u2510";
    const std::string rightLowerCorner = "\u2518";
    std::string horizontalBar;
    const std::string upperJunction = "\u252C";
    const std::string lowerJunction = "\u2534";

    // fills cells with possible number based on already filled cells
    void fillWithAllowedNumbers();
    void initializeBoarders();
    void initializeConstraintsMap();
    int getFlattenedCoord(int row, int col) const;
    int getFlattenedIndex(int row, int col) const;
    std::string getUpperHorizontalLine() const;
    std::string getLowerHorizontalLine() const;
    bool isNumPosValid(NumPosition num) const;
    // returns constrained cells specified in constraints
    std::vector<CellPtr> getCellsFromConstraints(CellPos cellPos) const;
    std::vector<CellPtr> getCellsFromColumn(CellPos cellPos) const;
    std::vector<CellPtr> getCellsFromRow(CellPos cellPos) const;
    // Checks if number is allowed before allowed numbers are set by fillWithAllowedNumbers
    bool isNumAllowed(NumPosition numPosition) const;
    std::string getHorizontalBar() const;
public:
    /**
     * @param initialBoard vector of NumPositions containing initial state of the board
     * @param constraints vector of vectors containing coordinates of cells where numbers cannot repeat
     */
    Sudoku(std::vector<NumPosition> initialBoard, std::vector<std::vector<CellPos>> constraints);
    /**
     * @return a string presenting the board after printing in console
     */
    std::string getBoardString() const;
    /**
     * @brief Checks if the given number can be put inside the given cell
     * @param numPosition a NumPosition value
     * @return true if the number can be put inside the cell
     */
    bool isNumberAllowed(NumPosition numPosition) const;
    /**
     * @param cellPos a CellPos value
     * @return the value of given cell
     */
    int getCellValue(CellPos cellPos) const;
    /**
     * @return true if sudoku is solved
     */
    bool isSolved() const;
    /**
     * @brief puts the given number in the given cell
     */
    void fillNumber(NumPosition) const;
    /**
     * @brief solves sudoku
     */
    void solve();

    virtual ~Sudoku();
};


#endif //SUDOKULOGIC_SUDOKU_H
