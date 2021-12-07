//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_ROW_H
#define SUDOKULOGICLIBRARY_ROW_H

#include <array>
#include "typedefs.h"
#include "CellUniqueGroup.h"

class CellVerifiers::Row: public CellVerifiers::CellUniqueGroup {
public:
    explicit Row(const std::vector<GameComponents::Cell::SharedPtr>& cells);
};

#endif //SUDOKULOGICLIBRARY_ROW_H
