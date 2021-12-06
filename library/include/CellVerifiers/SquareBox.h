//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_SQUAREBOX_H
#define SUDOKULOGICLIBRARY_SQUAREBOX_H

#include "CellUniqueGroup.h"

class CellVerifiers::SquareBox: public CellUniqueGroup{
public:
    explicit SquareBox(const std::vector<CellPtr> &cells);
};


#endif //SUDOKULOGICLIBRARY_SQUAREBOX_H
