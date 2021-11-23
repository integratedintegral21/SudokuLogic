//
// Created by wojciech on 23.11.2021.
//

#ifndef SUDOKULIBRARYTEST_CELLGROUP_H
#define SUDOKULIBRARYTEST_CELLGROUP_H

#include <vector>
#include "typedefs.h"


class CellGroup {
private:
    std::array<const CellPtr, 9> cells;
    std::array<CellPos, 9> cellPositions;
public:
    CellGroup(std::array<const CellPtr , 9> cells, std::array<const CellPos, 9> cellPositions);
    void updateAllowedNumbers();
    virtual void isNumberAllowed(NumPosition) = 0;
};


#endif //SUDOKULIBRARYTEST_CELLGROUP_H
