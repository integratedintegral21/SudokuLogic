//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_COLUMN_H
#define SUDOKULOGICLIBRARY_COLUMN_H

#include "CellUniqueGroup.h"

class CellVerifiers::Column: public CellVerifiers::CellUniqueGroup{
public:
    explicit Column(const std::vector<GameComponents::Cell::SharedPtr> &cells);
};

#endif //SUDOKULOGICLIBRARY_COLUMN_H
