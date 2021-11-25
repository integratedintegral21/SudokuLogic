//
// Created by wojciech on 23.11.2021.
//

#ifndef SUDOKULIBRARYTEST_CELLGROUP_H
#define SUDOKULIBRARYTEST_CELLGROUP_H

#include <vector>
#include "typedefs.h"

/**
 * Contains classes representing group of cells (rows, columns etc.)
 */
namespace CellVerifiers{
    /**
     * An abstract class representing a group of cells.
     * Any class inheriting from CellGroup must implement isNumberAllowedMethod
     */
    class CellGroup {
    protected:
        // Pointers to cells
        std::vector<CellPtr> cells;
    public:
        explicit CellGroup(const std::vector<CellPtr>& cells);
        /**
         * Checks if a number can be inserted based on other cells' numbers
         * @return true if the number can be inserted
         */
        virtual bool isNumberAllowed(int number) = 0;
    };
    class CellUniqueGroup;
    class Row;
    class Column;
    class SquareBox;
}


#endif //SUDOKULIBRARYTEST_CELLGROUP_H
