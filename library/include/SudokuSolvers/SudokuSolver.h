//
// Created by wojciech on 14/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_SUDOKUSOLVER_H
#define SUDOKULOGICLIBRARY_SUDOKUSOLVER_H

#include "Solvers.h"
#include "GameComponents/Sudoku.h"
#include "memory"

class Solvers::SudokuSolver {
public:
    virtual std::shared_ptr<GameComponents::Sudoku> solve(const std::shared_ptr<GameComponents::Sudoku>& sudoku) = 0;

    typedef std::shared_ptr<Solvers::SudokuSolver> SharedPtr;
};


#endif //SUDOKULOGICLIBRARY_SUDOKUSOLVER_H
