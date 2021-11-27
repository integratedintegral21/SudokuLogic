//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_COLUMN_H
#define SUDOKULOGICLIBRARY_COLUMN_H

#include "CellUniqueGroup.h"

class CellVerifiers::Column: public CellVerifiers::CellUniqueGroup{
public:
    explicit Column(const std::vector<CellPtr> &cells);
};

#endif //SUDOKULOGICLIBRARY_COLUMN_H
