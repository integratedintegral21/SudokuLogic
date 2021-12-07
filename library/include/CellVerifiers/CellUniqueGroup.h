//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H
#define SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H

#include "CellGroup.h"
#include "GameComponents/Cell.h"

using GameComponents::Cell;

class CellVerifiers::CellUniqueGroup: public CellGroup{
    bool usedNumberMask[9];
public:
    /**
     * @param cells a vector of shared pointers to Cell objects
     */
    explicit CellUniqueGroup(const std::vector<Cell::SharedPtr> &cells);
    /**
     * @param number A tested number
     * @return false if the number is already in a group object. True otherwise
     */
    bool isNumberAllowed(int number) const override;

    void notifyAdd(int number) override;

    void notifyRemove(int number) override;
};



#endif //SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H
