//
// Created by wojciech on 23.11.2021.
//

#ifndef SUDOKULIBRARYTEST_CELLGROUP_H
#define SUDOKULIBRARYTEST_CELLGROUP_H

#include <vector>
#include "typedefs.h"


class CellGroup {
private:
    // Pointers to cells
    std::array<CellPtr, 9> cells;
    // Cell's coordinates
    std::array<CellPos, 9> cellPositions;
protected:
    /**
     * Checks if a number can be inserted based on other cells' number
     * @return true if the number can be inserted
     */
    virtual bool isNumberAllowed(NumPosition) = 0;
public:
    explicit CellGroup(std::array<CellPtr , 9> cells);
    /**
     * Sets allowed numbers in each cell from scratch. Use setNumberNotAllowed if possible
     */
    void updateAllowedNumbers();
    /**
     * Sets given number as not allowed in a CellGroup. Use after inserting a number
     * @param number the number to be not allowed in a CellGroup
     */
    void setNumberNotAllowed(int number);
};


#endif //SUDOKULIBRARYTEST_CELLGROUP_H
