//
// Created by wojciech on 01/08/2021.
//

#include <typedefs.h>
#include <vector>
#include <tuple>
#include <utils.h>
#include <Sudoku.h>
#include <thread>


using namespace std;

vector<vector<CellPos>> getSimpleConstraints(){
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

Sudoku solveSudoku(Sudoku sudoku) {
    if(sudoku.isSolved()){
        return sudoku;
    }
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
        threads.emplace_back(thread(solverWrapper, thSudoku));
    }
    for(auto& th: threads){
        th.join();
    }
    for(SudokuPtr thSudoku: threadedSudokus){
        if(thSudoku->isSolved()){
            return *thSudoku;
        }
    }
}
