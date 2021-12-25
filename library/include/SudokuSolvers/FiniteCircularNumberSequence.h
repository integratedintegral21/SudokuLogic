//
// Created by wojciech on 25/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_FINITECIRCULARNUMBERSEQUENCE_H
#define SUDOKULOGICLIBRARY_FINITECIRCULARNUMBERSEQUENCE_H

#include "SudokuSolvers/Solvers.h"
#include "FiniteNumberSequence.h"

class Solvers::FiniteCircularNumberSequence: public Solvers::FiniteNumberSequence{
private:
    int first, last;
public:
    FiniteCircularNumberSequence(int first, int last, int start);
};


#endif //SUDOKULOGICLIBRARY_FINITECIRCULARNUMBERSEQUENCE_H
