//
// Created by wojciech on 28/07/2021.
//

#ifndef SUDOKULOGIC_SUDOKU_H
#define SUDOKULOGIC_SUDOKU_H

#include <vector>
#include <string>
#include <map>
#include "typedefs.h"
#include "CellUniqueGroup.h"
#include "Row.h"
#include "Column.h"
#include "SquareBox.h"


class Sudoku {
private:
    // flattened 9x9 board
    std::vector<CellPtr> board;
    // assigns constrained cells to every Cell
    std::vector<std::vector<int>> constraintsList;
    // list containing cell separators
    std::vector<std::vector<std::string>> verticalBorders;

    const std::string verticalSeparator = "│";
    const std::string leftUpperCorner = "┌";
    const std::string leftLowerCorner = "└";
    const std::string rightUpperCorner = "┐";
    const std::string rightLowerCorner = "┘";
    std::string longHorizontalBar;
    std::string shortHorizontalBar;
    const std::string upperJunction = "┬";
    const std::string lowerJunction = "┴";

    std::vector<CellVerifiers::CellUniqueGroup> rows;
    std::vector<CellVerifiers::CellUniqueGroup> cols;
    std::vector<CellVerifiers::CellUniqueGroup> boxes;

    // clears allowed numbers and fills cells with allowed number based on non-empty filled cells
    void fillWithAllowedNumbers();
    void fillWithAllowedNumbers(CellPos & cellPos);
    void initializeBorders();
    // initializes constraintsList
    void initializeConstraintsList(const std::vector<std::vector<CellPos>>& constraints);
    static int getFlattenedCoord(int row, int col) ;
    int getFlattenedIndex(int row, int col) const;
    std::string getUpperHorizontalLine(bool isLong) const;
    std::string getLowerHorizontalLine(bool isLong) const;
    static bool isNumPosValid(NumPosition num) ;
    static bool isCellPosValid(CellPos) ;
    // returns constrained cells specified in constraints
    std::vector<int> getCellIndexesFromConstraints(CellPos cellPos, const std::vector<std::vector<CellPos>>&) const;
    std::vector<int> getCellsFromColumn(CellPos cellPos) const;
    std::vector<int> getCellsFromRow(CellPos cellPos) const;
    // Checks if number is allowed before allowed numbers are set by fillWithAllowedNumbers
    bool isNumAllowed(NumPosition numPosition);
    static std::string getHorizontalBar(bool isLong) ;
    static NumPosition buildNumPos(int flattenedCoord, int num) ;
    void pruneNumber(NumPosition numPosition);
    void solveByPruning(int entryFlattenedCoord);
    bool isSolvedFrom(int entryFlattenedCoord);
    bool uniqueInPositions(const std::vector<int>& indexes, int num) const;
public:
    /**
     * @brief calls 2-arguments constructor with simple constraints (classic sudoku puzzle)
     * @param initialBoard vector of NumPositions containing initial state of the board. Throws invalid_argument
     */
    explicit Sudoku(const std::vector<NumPosition>& initialBoard);
    /**
     * @param initialBoard vector of NumPositions containing initial state of the board. Throws invalid_argument
     * @param constraints vector of vectors containing coordinates of cells where numbers cannot repeat
     */
    Sudoku(const std::vector<NumPosition>& initialBoard, const std::vector<std::vector<CellPos>>& constraints);
    Sudoku(const Sudoku& sudoku);
    /**
     * @param showAllowedNumbers the function includes allowed numbers in the string if true
     * @return a string presenting the board after printing in console
     */
    std::string getBoardString(bool showAllowedNumbers = false) const;
    /**
     * @brief Checks if the given number can be put inside the given cell. Throws invalid_argument
     * @param numPosition specifies coordinates of the cell and the candidate number (row, column, number) tuple.
     * 1 <= row, column, number <= 9
     * @return true if the number can be put inside the cell
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
     * @param numPosition coordinates of the cell and target value (row, column, value) tuple. 1 <= row, column, number <= 9
     */
    void setNumber(NumPosition numPosition);
    /**
     * @brief clears the value of the given cell and updates cells' allowed numbers. Throws invalid_argument
     * @param cellPos coordinates of the cell (row, column) tuple, 1 <= row, column <= 9
     */
    void unsetCell(CellPos cellPos);
    /**
     * @brief solves sudoku by pruning
     */
    void solve();
    /**
     * @brief returns all allowed numbers of given cell
     * @param flattenedCoord specifies the cell
     * @return vector of allowed values (integers)
     */
    std::vector<int> getAllowedNumbers(int flattenedCoord) const;
    virtual ~Sudoku();
};


#endif //SUDOKULOGIC_SUDOKU_H
