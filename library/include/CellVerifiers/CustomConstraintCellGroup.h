//
// Created by wojciech on 27.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H
#define SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H

#include "CellGroup.h"
#include "functional"
#include "GameComponents/Cell.h"

class CellVerifiers::CustomConstraintCellGroup: public CellVerifiers::CellGroup{
protected:
    // Returns true if cells hold given condition
    std::function<bool(const std::vector<GameComponents::Cell::SharedPtr>&, int)> constraint;
public:
    /**
     * Constructor
     * @param cells A vector of list of shared pointers to cells
     * @param constraint A predicate which all cells in the group and a candidate number must hold
     */
    CustomConstraintCellGroup(const std::vector<GameComponents::Cell::SharedPtr> &cells,
                              std::function<bool(const std::vector<GameComponents::Cell::SharedPtr>&, int)> constraint);
    bool isNumberAllowed(int number) const override;

    void notifyAdd(int number) override;

    void notifyRemove(int number) override;
};


#endif //SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H
