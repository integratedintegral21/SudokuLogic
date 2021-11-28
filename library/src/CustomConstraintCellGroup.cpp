//
// Created by wojciech on 27.11.2021.
//

#include "CustomConstraintCellGroup.h"
#include <utility>

CellVerifiers::CustomConstraintCellGroup::CustomConstraintCellGroup(
        const std::vector<CellPtr> &cells,
        std::function<bool(const std::vector<CellPtr>&, int)>  constraint): CellVerifiers::CellGroup(cells),
        constraint(std::move(constraint)){}

bool CellVerifiers::CustomConstraintCellGroup::isNumberAllowed(int number) const{
    return this->constraint(this->cells, number);
}


