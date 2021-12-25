//
// Created by wojciech on 12/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_CELLGROUPOBSERVER_H
#define SUDOKULOGICLIBRARY_CELLGROUPOBSERVER_H

#include "CellVerifiers.h"
#include "memory"

class CellVerifiers::CellGroupObserver {
public:
    /**
     * Notifies a group object when a number is set in a cell
     * @param number
     */
    virtual void notifySet(int number) = 0;

    /**
     * Notifies a group object when a number is unset in a cell
     * @param number
     */
    virtual void notifyClear(int number) = 0;

    /**
     * Returns true if given number can be set in one of group's cells
     * @param number
     * @return true if the number can be set, false otherwise
     */
    [[nodiscard]] virtual bool isNumberAllowed(int number) const = 0;

    /**
     * Returns a deep copy of the current object
     * @return a shred pointer to the copy
     */
    virtual std::shared_ptr<CellVerifiers::CellGroupObserver> clone() const = 0;

    typedef std::shared_ptr<CellVerifiers::CellGroupObserver> SharedPtr;
};


#endif //SUDOKULOGICLIBRARY_CELLGROUPOBSERVER_H
