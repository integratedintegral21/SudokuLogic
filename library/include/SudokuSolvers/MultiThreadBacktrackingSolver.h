//
// Created by wojciech on 14/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_MULTITHREADBACKTRACKINGSOLVER_H
#define SUDOKULOGICLIBRARY_MULTITHREADBACKTRACKINGSOLVER_H

#include "SudokuSolver.h"

class Solvers::MultiThreadBacktrackingSolver: public SudokuSolver{
public:
    std::shared_ptr<GameComponents::Sudoku> solve(const std::shared_ptr<GameComponents::Sudoku> &sudoku) override;

};


#endif //SUDOKULOGICLIBRARY_MULTITHREADBACKTRACKINGSOLVER_H
