//
// Created by wojciech on 26/12/2021.
//

#include "SudokuSolvers/CircularSubsequentNumbersSequence.h"

Solvers::CircularSubsequentNumbersSequence::CircularSubsequentNumbersSequence(int first, int last, int start): first(first), last(last), start(start)  {
    if (first > last){
        throw std::logic_error("The first number must be less or equal the last number in the sequence");
    }
    if (start < first || start > last){
        throw std::logic_error("The starting number must be between the first and the last number");
    }
}
