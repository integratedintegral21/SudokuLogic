//
// Created by wojciech on 13/12/2021.
//

#include "GameComponents/Sudoku.h"
#include "CellVerifiers/CellGroupObserver.h"
#include <stdexcept>

using namespace std;

int GameComponents::Sudoku::getCellIndex(int row, int column) {
    return NR_COLUMNS * row + column;
}

bool GameComponents::Sudoku::isNumberAllowed(int row, int column, int number) const {
    if (row < 0 || row >= NR_ROWS || column < 0 || column > NR_COLUMNS || number < 1 || number > 9){
        return false;
    }
    int cellIndex = getCellIndex(row, column);
    Cell::SharedPtr cell = this->cells[cellIndex];
    vector<CellVerifiers::CellGroupObserver::SharedPtr> groups = cell->getGroups();
    for (const auto &group: groups) {
        if (!group->isNumberAllowed(number)){
            return false;
        }
    }
    return true;
}

void GameComponents::Sudoku::setNumber(int row, int column, int number) {
    if (!isNumberAllowed(row, column, number)){
        throw invalid_argument("The given number is not allowed");
    }
    int cellIndex = getCellIndex(row, column);
    Cell::SharedPtr cell = this->cells[cellIndex];
    cell->setNumber(number);
}
