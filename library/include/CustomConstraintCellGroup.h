//
// Created by wojciech on 27.11.2021.
//

#ifndef SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H
#define SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H

#include "CellGroup.h"
#include "functional"

namespace CellVerifiers{
    class CustomConstraintCellGroup: public CellVerifiers::CellGroup{
    protected:
        // Returns true if cells hold given condition
        std::function<bool(const std::vector<CellPtr>&, int)> constraint;
    public:
        /**
         * Constructor
         * @param cells A vector of list of shared pointers to cells
         * @param constraint A predicate which all cells in the group and a candidate number must hold
         */
        CustomConstraintCellGroup(const std::vector<CellPtr> &cells,
                                  std::function<bool(const std::vector<CellPtr>&, int)> constraint);
        bool isNumberAllowed(int number) override;
    };
}

#endif //SUDOKULOGICLIBRARY_CUSTOMCONSTRAINTCELLGROUP_H
