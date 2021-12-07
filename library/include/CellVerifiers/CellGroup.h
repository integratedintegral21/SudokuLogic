//
// Created by wojciech on 23.11.2021.
//

#ifndef SUDOKULIBRARYTEST_CELLGROUP_H
#define SUDOKULIBRARYTEST_CELLGROUP_H

#include <vector>
#include "typedefs.h"
#include "memory"
#include "CellVerifiers/CellVerifiers.h"
#include "GameComponents/GameComponents.h"

/**
 * A class representing a group of cells.
 * Any class inheriting from CellGroup must implement isNumberAllowed, notifyAdd, notifyRemove
 */
class CellVerifiers::CellGroup{
protected:
    // Pointers to cells
    std::vector<std::shared_ptr<GameComponents::Cell>> cells;
public:
    explicit CellGroup(const std::vector<std::shared_ptr<GameComponents::Cell>>& cells);
    /**
     * Checks if a number can be inserted based on other cells' numbers
     * @return true if the number can be inserted
     */
    virtual bool isNumberAllowed(int number) const = 0;
    /**
     * Returns a list of cells in a group
     * @return a vector of shared pointers to cells
     */
    virtual std::vector<std::shared_ptr<GameComponents::Cell>> getCells() const;
    /**
     * Called by a cell when a number is set in it
     * @param number
     */
    virtual void notifyAdd(int number) = 0;
    /**
     * Called by a cell when it is cleared
     * @param number
     */
    virtual void notifyRemove(int number) = 0;

    virtual ~CellGroup();

    //-----------------------------------------

    typedef std::shared_ptr<CellGroup> SharedPtr;
};


#endif //SUDOKULIBRARYTEST_CELLGROUP_H
