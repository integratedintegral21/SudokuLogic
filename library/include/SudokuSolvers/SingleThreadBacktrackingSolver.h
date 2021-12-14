//
// Created by wojciech on 14/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_SINGLETHREADBACKTRACKINGSOLVER_H
#define SUDOKULOGICLIBRARY_SINGLETHREADBACKTRACKINGSOLVER_H

#include "SudokuSolver.h"

class Solvers::SingleThreadBacktrackingSolver: public SudokuSolver{
public:
    std::shared_ptr<GameComponents::Sudoku> solve(const std::shared_ptr<GameComponents::Sudoku> &sudoku) override;

};


#endif //SUDOKULOGICLIBRARY_SINGLETHREADBACKTRACKINGSOLVER_H
