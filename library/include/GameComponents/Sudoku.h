//
// Created by wojciech on 13/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_SUDOKU_H
#define SUDOKULOGICLIBRARY_SUDOKU_H


#include "GameComponents/GameComponents.h"
#include "GameComponents/Cell.h"
#include "typedefs.h"
#include <vector>

class GameComponents::Sudoku {
private:
    const static int NR_ROWS = 9;
    const static int NR_COLUMNS = 9;
    // 81 cells
    std::vector<Cell::SharedPtr> cells;

    // assumes row and column indices start from 0
    static int getCellIndex(int row, int column);
public:
    /**
     * Checks if a given number is allowed to be set at a given position
     * @param row 0 <= row <= 8
     * @param column 0 <= column <= 8
     * @param number 1 <= number <= 9
     * @return true if the number can be set, false otherwise
     */
    [[nodiscard]] bool isNumberAllowed(int row, int column, int number) const;
    /**
     * Sets number at given cell
     * @param row 0 <= row <= 8
     * @param column 0 <= column <= 8
     * @param number 1 <= number <= 9
     * @throw invalid_argument if the number is not allowed at given position
     */
    void setNumber(int row, int column, int number);
};


#endif //SUDOKULOGICLIBRARY_SUDOKU_H
