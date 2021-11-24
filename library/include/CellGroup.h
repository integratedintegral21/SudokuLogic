//
// Created by wojciech on 23.11.2021.
//

#ifndef SUDOKULIBRARYTEST_CELLGROUP_H
#define SUDOKULIBRARYTEST_CELLGROUP_H

#include <vector>
#include "typedefs.h"


class CellGroup {
private:
    std::array<CellPtr, 9> cells;
    std::array<CellPos, 9> cellPositions;
protected:
    /**
     * Checks if a number can be inserted based on other cells' number
     * @return true if the number can be inserted
     */
    virtual bool isNumberAllowed(NumPosition) = 0;
public:
    CellGroup(std::array<CellPtr , 9> cells, std::array<CellPos, 9> cellPositions);
    void updateAllowedNumbers();
};


#endif //SUDOKULIBRARYTEST_CELLGROUP_H
