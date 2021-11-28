//
// Created by wojciech on 01/08/2021.
//

#include <typedefs.h>
#include <vector>
#include <tuple>
#include <utils.h>
#include <Sudoku.h>
#include <thread>
#include "Cell.h"


using namespace std;

vector<vector<CellPos>> Utils::getSimpleConstraints(){
    vector<vector<CellPos>> simpleConstraints;
    for (int sqRow = 0 ; sqRow <= 2 ; sqRow++){
        for (int sqCol = 0 ; sqCol <= 2 ; sqCol++){
            vector<CellPos> square;
            for (int i = 0 ; i <= 2; i++){
                for (int j = 0 ; j <= 2; j++){
                    square.push_back(make_tuple(3 * sqRow + i + 1, 3 * sqCol + j + 1));
                }
            }
            simpleConstraints.push_back(square);
        }
    }
    return simpleConstraints;
}

void solverWrapper(SudokuPtr sudoku){
    sudoku->solve();
}

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

function<bool(const vector<CellPtr>&, int)> Utils::getSumConstraints(int expectedSum) {
    return [expectedSum](const vector<CellPtr> &cells, int candidateNum) {
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