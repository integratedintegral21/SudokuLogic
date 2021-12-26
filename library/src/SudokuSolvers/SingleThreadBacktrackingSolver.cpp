//
// Created by wojciech on 14/12/2021.
//

#include "SudokuSolvers/SingleThreadBacktrackingSolver.h"
#include "SudokuSolvers/CircularSubsequentNumbersSequence.h"

std::shared_ptr<GameComponents::Sudoku>
Solvers::SingleThreadBacktrackingSolver::solve(const std::shared_ptr<GameComponents::Sudoku> &sudoku) {
    // start from 1 in each cell
    std::vector<std::unique_ptr<CircularSubsequentNumbersSequence>> circularSequences(81);
    std::vector<std::unique_ptr<CircularSubsequentNumbersSequence::Iterator>> circularSequencesIterators(81);
    for (int i = 0; i < 81; i++) {
        circularSequences[i] = std::make_unique<CircularSubsequentNumbersSequence>(1, 9, 1);
        circularSequencesIterators[i] = std::make_unique<CircularSubsequentNumbersSequence::Iterator>(circularSequences[i]->beginIt());
    }
    // masking of immutable cells
    bool fixedMask[9][9];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            // true if a cell is not empty
            fixedMask[i][j] = sudoku->getNumber(i, j) != 0;
        }
    }
    for (int cellIndex = 0; cellIndex < 81; cellIndex++){
        int rowIndex = cellIndex / 9;
        int columnIndex = cellIndex % 9;
        bool isSolvable = false;
        // going forward to a cell for the first time
        if (sudoku->getNumber(rowIndex, columnIndex) == 0){
            int candidateNumber = **(circularSequencesIterators[cellIndex]);
            (*circularSequencesIterators[cellIndex])++;

        }
        // going back or the cell is fixed
        else{

        }
    }
}
