//
// Created by wojciech on 25.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H
#define SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H

#include "CellGroup.h"

class CellVerifiers::CellUniqueGroup: public CellGroup{
public:
    /**
     * @param cells a vector of shared pointers to Cell objects
     */
    explicit CellUniqueGroup(const std::vector<CellPtr> &cells);
    /**
     * @param number A tested number
     * @return false if the number is already in a group object. True otherwise
     */
    bool isNumberAllowed(int number) override;
};



#endif //SUDOKULOGICLIBRARY_CELLUNIQUEGROUP_H
