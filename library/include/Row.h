//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_ROW_H
#define SUDOKULOGICLIBRARY_ROW_H

#include <array>
#include "typedefs.h"
#include "CellUniqueGroup.h"

namespace CellVerifiers{
    class Row: public CellVerifiers::CellUniqueGroup {
    public:
        explicit Row(const std::vector<CellPtr>& cells);
    };
}



#endif //SUDOKULOGICLIBRARY_ROW_H
