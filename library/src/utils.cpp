//
// Created by wojciech on 01/08/2021.
//

#include <typedefs.h>
#include <vector>
#include <tuple>
#include <utils.h>
#include <GameComponents/Sudoku.h>
#include <thread>
#include "GameComponents/Cell.h"
#include "iostream"


using namespace std;
using namespace CellVerifiers;
using namespace GameComponents;

/*
void solverWrapper(SudokuPtr sudoku){
    sudoku->solve();
}
*/
std::vector<CellVerifiers::CellGroup::SharedPtr> Utils::getSimpleGroups(const std::vector<Cell::SharedPtr>& cells){
    if (cells.size() != 81){
        throw invalid_argument("Cells' array size should be 81");
    }
    vector<CellVerifiers::CellGroup::SharedPtr> rows(9);
    vector<CellVerifiers::CellGroup::SharedPtr> cols(9);
    vector<CellVerifiers::CellGroup::SharedPtr> boxes(9);
    for (int i = 0 ; i < 9 ; i++){
        vector<Cell::SharedPtr> rowCells(9);
        vector<Cell::SharedPtr> colCells(9);
        vector<Cell::SharedPtr> boxCells(9);
        for (int j = 0 ; j < 9 ; j++){
            rowCells[j] = cells[9 * i + j];
            colCells[j] = cells[9 * j + i];
        }
        int boxInitialRow = i / 3 * 3;
        int boxInitialCol = i % 3 * 3;
        for (int rowOffset = 0; rowOffset <= 2; rowOffset++){
            for (int colOffset = 0; colOffset <= 2; colOffset++){
                boxCells[3 * rowOffset + colOffset] = cells[9 * (boxInitialRow + rowOffset) + (boxInitialCol + colOffset)];
            }
        }
        rows[i] = make_shared<CellVerifiers::Row>(rowCells);
        cols[i] = make_shared<CellVerifiers::Column>(colCells);
        boxes[i] = make_shared<CellVerifiers::SquareBox>(boxCells);
    }
    vector<CellVerifiers::CellGroup::SharedPtr> concatenatedGroups(rows);
    concatenatedGroups.insert(
            concatenatedGroups.end(),
            make_move_iterator(cols.begin()),
            make_move_iterator(cols.end())
            );
    concatenatedGroups.insert(
            concatenatedGroups.end(),
            make_move_iterator(boxes.begin()),
            make_move_iterator(boxes.end())
    );
    return concatenatedGroups;
}
/*
Sudoku Utils::solveSudoku(const Sudoku &sudoku) {
    if(sudoku.isSolved()){
        return sudoku;
    }
    // looks for the cell with the largest number of allowed numbers
    int maxAllowedNumbers = 0;
    int maxAllowedNumbersCoord = 1;
    for(int i = 1 ; i <= 81 ; i++){
        vector<int> allowedNumbers = sudoku.getAllowedNumbers(i);
        if(allowedNumbers.size() > maxAllowedNumbers){
            maxAllowedNumbers = allowedNumbers.size();
            maxAllowedNumbersCoord = i;
        }
    }
    vector<SudokuPtr> threadedSudokus;
    vector<int> allowedNumbers = sudoku.getAllowedNumbers(maxAllowedNumbersCoord);
    for(int num: allowedNumbers){
        SudokuPtr sudokuCopy = make_shared<Sudoku>(sudoku);
        int row = (maxAllowedNumbersCoord - 1) / 9 + 1;
        int col = (maxAllowedNumbersCoord - 1) % 9 + 1;
        NumPosition numPosition = make_tuple(row, col, num);
        sudokuCopy->setNumber(numPosition);
        threadedSudokus.push_back(sudokuCopy);
    }
    vector<thread> threads;
    for(SudokuPtr thSudoku: threadedSudokus){
        threads.emplace_back(thread([](SudokuPtr sudoku){sudoku->solve();}, thSudoku));
    }
    for(auto& th: threads){
        th.join();
    }
    for(SudokuPtr thSudoku: threadedSudokus){
        if(thSudoku->isSolved()){
            return *thSudoku;
        }
    }
    return sudoku;
}
*/
function<bool(const vector<Cell::SharedPtr>&, int)> Utils::getSumConstraints(int expectedSum) {
    return [expectedSum](const vector<Cell::SharedPtr> &cells, int candidateNum) {
        // is the candidateNumber the last to add
        bool finalNum = true;
        int emptyCount = 0;
        // checking if there is exactly one free slot
        auto init = cells.begin();
        auto end = cells.end();
        for(auto current = init; current < end; current++){
            if ((*current)->isEmpty()) {
                emptyCount++;
            }
            // more than one empty cell, the candidate number is not final
            if (emptyCount >= 2) {
                finalNum = false;
            }
        }
        // no more slots available, return false
        if(emptyCount == 0){
            return false;
        }
        int sum = 0;
        for(auto current = init; current < end; current++){
            // count a cell only if it is not empty
            sum += (*current)->getNumber() * !(*current)->isEmpty();
        }
        if (finalNum) {
            // the sum of all cells and the candidate number must add up to the desired value
            return sum + candidateNum == expectedSum;
        }
        // otherwise, check if there is 'space' for next candidate numbers
        return sum + candidateNum < expectedSum;
    };
}

std::vector<Cell::SharedPtr> Utils::getCellsFromNumPoses(const std::vector<NumPosition> &numPositions) {
    if (numPositions.size() > 81) {
        throw invalid_argument("More than 81 numPositions given, so the board is over-defined");
    }
    std::vector<Cell::SharedPtr> cells(81);
    // initialize empty cells
    for (Cell::SharedPtr& cell: cells){
        cell = make_shared<Cell>();
    }
    for (const NumPosition& numPosition: numPositions){
        int row = std::get<0>(numPosition) - 1;
        int col = std::get<1>(numPosition) - 1;
        int num = std::get<2>(numPosition);
        if (row < 0 || row > 8 || col < 0 | col > 8 || num < 1 || num > 9){
            throw invalid_argument("Invalid row/col/num value");
        }
        int cellIndex = 9 * row + col;
        Cell::SharedPtr cell = cells[cellIndex];
        if (!cell->isEmpty()){
            throw invalid_argument("Over-definition error. Some cell is defined by more than 1 numPosition");
        }
        cell->setNumber(num);
    }
    return cells;
}
