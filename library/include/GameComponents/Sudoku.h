//
// Created by wojciech on 28/07/2021.
//

#ifndef SUDOKULOGIC_SUDOKU_H
#define SUDOKULOGIC_SUDOKU_H

#include <vector>
#include <string>
#include <map>
#include "typedefs.h"
#include "CellVerifiers/CellUniqueGroup.h"
#include "CellVerifiers/Row.h"
#include "CellVerifiers/Column.h"
#include "CellVerifiers/SquareBox.h"
#include "GameComponents/GameComponents.h"


class GameComponents::Sudoku {
private:
    // flattened 9x9 board
    std::vector<CellPtr> board;
public:
    virtual ~Sudoku();
};


#endif //SUDOKULOGIC_SUDOKU_H
