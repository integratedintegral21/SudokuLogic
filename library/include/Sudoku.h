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
    // assigns constrained cells to every Cell
    std::map<CellPtr, std::vector<CellPtr>> constraintsMap;
    // list containing cell separators
    std::vector<std::vector<std::string>> verticalBoarders;

    const std::string verticalSeparator = "\u2502";
    const std::string leftUpperCorner = "\u250C";
    const std::string leftLowerCorner = "\u2514";
    const std::string rightUpperCorner = "\u2510";
    const std::string rightLowerCorner = "\u2518";
    std::string longHorizontalBar;
    std::string shortHorizontalBar;
    const std::string upperJunction = "\u252C";
    const std::string lowerJunction = "\u2534";

    // clears allowed numbers and fills cells with allowed number based on non-empty filled cells
    void fillWithAllowedNumbers();
    void initializeBoarders();
    // initializes constraintsMap
    void initializeConstraintsMap(std::vector<std::vector<CellPos>>);
    int getFlattenedCoord(int row, int col) const;
    int getFlattenedIndex(int row, int col) const;
    std::string getUpperHorizontalLine(bool isLong) const;
    std::string getLowerHorizontalLine(bool isLong) const;
    bool isNumPosValid(NumPosition num) const;
    bool isCellPosValid(CellPos) const;
    // returns constrained cells specified in constraints
    std::vector<CellPtr> getCellsFromConstraints(CellPos cellPos, std::vector<std::vector<CellPos>>&) const;
    std::vector<CellPtr> getCellsFromColumn(CellPos cellPos) const;
    std::vector<CellPtr> getCellsFromRow(CellPos cellPos) const;
    // Checks if number is allowed before allowed numbers are set by fillWithAllowedNumbers
    bool isNumAllowed(NumPosition numPosition);
    std::string getHorizontalBar(bool isLong) const;
    NumPosition buildNumPos(int flattenedCoord, int num) const;
    void solveByPruning(int entryFlattenedCoord);
    bool isSolvedFrom(int entryFlattenedCoord);
public:
    /**
     * @param initialBoard vector of NumPositions containing initial state of the board. Throws invalid_argument
     * @param constraints vector of vectors containing coordinates of cells where numbers cannot repeat
     */
    Sudoku(std::vector<NumPosition> initialBoard, std::vector<std::vector<CellPos>> constraints);
    /**
     * @param showAllowedNumbers the function includes allowed numbers in the string if true
     * @return a string presenting the board after printing in console
     */
    std::string getBoardString(bool showAllowedNumbers = false) const;
    /**
     * @brief Checks if the given number can be put inside the given cell. Throws invalid_argument
     * @param numPosition specifies coordinates of the cell and the candidate number (row, column, number) tuple
     * ; 1 <= row, column, number <= 9
     * @return true if the number can be put inside the cell or if is already there.
     */
    bool isNumberAllowed(NumPosition numPosition) const;
    /**
     * @param cellPos specifies the cell (row, column) tuple; 1 <= row, column <= 9
     * @return the value of the given cell (-1 if empty)
     */
    int getCellValue(CellPos cellPos) const;
    /**
     * @return true if sudoku is solved (every cell is filled)
     */
    bool isSolved() const;
    /**
     * @brief puts the given number in the given cell if allowed and updates cells' allowed numbers. Throws invalid_argument
     * ; 1 <= row, column, number <= 9
     * @param numPosition coordinates of the cell and target value (row, column, value) tuple
     */
    void setNumber(NumPosition numPosition);
    /**
     * @brief clears the value of the given cell and updates cells' allowed numbers. Throws invalid_argument
     * ; 1 <= row, column <= 9
     * @param cellPos coordinates of the cell (row, column) tuple
     */
    void unsetCell(CellPos cellPos);
    /**
     * @brief solves sudoku by pruning
     */
    void solve();
    std::vector<int> getAllowedNumbers(int flattenedCoord) const;
    virtual ~Sudoku();
};


#endif //SUDOKULOGIC_SUDOKU_H
