//
// Created by wojciech on 25/12/2021.
//

#include "SudokuSolvers/FiniteCircularNumberSequence.h"
#include <stdexcept>

Solvers::FiniteCircularNumberSequence::FiniteCircularNumberSequence(int first, int last, int start): first(first), last(last) {
    if (last < first){
        throw std::logic_error("The first number must be less or equal the last number");
    }
    if (start < first || start > last){
        throw std::logic_error("The starting number needs to be between the first and the last number in the sequence");
    }
}
