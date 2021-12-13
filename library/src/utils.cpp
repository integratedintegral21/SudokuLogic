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
#include "CellVerifiers/CellGroupObserver.h"
#include "CellVerifiers/UniqueCellGroup.h"
#include <stdexcept>


using namespace std;
using GameComponents::Cell;
using CellVerifiers::CellGroupObserver;
using CellVerifiers::UniqueCellGroup;

///*
//void solverWrapper(SudokuPtr sudoku){
//    sudoku->solve();
//}
//*/

///*
//Sudoku Utils::solveSudoku(const Sudoku &sudoku) {
//    if(sudoku.isSolved()){
//        return sudoku;
//    }
//    // looks for the cell with the largest number of allowed numbers
//    int maxAllowedNumbers = 0;
//    int maxAllowedNumbersCoord = 1;
//    for(int i = 1 ; i <= 81 ; i++){
//        vector<int> allowedNumbers = sudoku.getAllowedNumbers(i);
//        if(allowedNumbers.size() > maxAllowedNumbers){
//            maxAllowedNumbers = allowedNumbers.size();
//            maxAllowedNumbersCoord = i;
//        }
//    }
//    vector<SudokuPtr> threadedSudokus;
//    vector<int> allowedNumbers = sudoku.getAllowedNumbers(maxAllowedNumbersCoord);
//    for(int num: allowedNumbers){
//        SudokuPtr sudokuCopy = make_shared<Sudoku>(sudoku);
//        int row = (maxAllowedNumbersCoord - 1) / 9 + 1;
//        int col = (maxAllowedNumbersCoord - 1) % 9 + 1;
//        NumPosition numPosition = make_tuple(row, col, num);
//        sudokuCopy->setNumber(numPosition);
//        threadedSudokus.push_back(sudokuCopy);
//    }
//    vector<thread> threads;
//    for(SudokuPtr thSudoku: threadedSudokus){
//        threads.emplace_back(thread([](SudokuPtr sudoku){sudoku->solve();}, thSudoku));
//    }
//    for(auto& th: threads){
//        th.join();
//    }
//    for(SudokuPtr thSudoku: threadedSudokus){
//        if(thSudoku->isSolved()){
//            return *thSudoku;
//        }
//    }
//    return sudoku;
//}

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

vector<Cell::SharedPtr> Utils::getSimpleSudokuCells(const vector<Cell::SharedPtr> &cells) {
    if (cells.size() != 81){
        throw invalid_argument("Number of cells is not 81");
    }
    vector<CellGroupObserver::SharedPtr> rows(9);
    vector<CellGroupObserver::SharedPtr> columns(9);
    vector<CellGroupObserver::SharedPtr> boxes(9);

    for (int i = 0 ; i < 9 ; i++){
        rows[i] = make_shared<UniqueCellGroup>();
        columns[i] = make_shared<UniqueCellGroup>();
        boxes[i] = make_shared<UniqueCellGroup>();
    }

    for (int i = 0; i < 81; ++i) {
        Cell::SharedPtr cell = cells[i];
        int rowIndex = i / 9;
        int columnIndex = i % 9;
        int boxIndex = (rowIndex / 3) * 3 + (columnIndex / 3);
        cell->addGroupObserver(rows[rowIndex]);
        cell->addGroupObserver(columns[columnIndex]);
        cell->addGroupObserver(boxes[boxIndex]);
        if (!cell->isEmpty()){
            if (!rows[rowIndex]->isNumberAllowed(cell->getNumber()) ||
                !columns[rowIndex]->isNumberAllowed(cell->getNumber()) ||
                !boxes[rowIndex]->isNumberAllowed(cell->getNumber())){
                throw invalid_argument("At least one cell is not unique in its groups");
            }
            // add the number inside the cell to not allowed
            rows[rowIndex]->notifySet(cell->getNumber());
            columns[rowIndex]->notifySet(cell->getNumber());
            boxes[rowIndex]->notifySet(cell->getNumber());
        }
    }
    return {cells};
}
