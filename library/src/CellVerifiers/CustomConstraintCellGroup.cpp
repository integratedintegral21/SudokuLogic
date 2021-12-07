//
// Created by wojciech on 27.11.2021.
//

#include "CellVerifiers/CustomConstraintCellGroup.h"
#include <utility>

using namespace GameComponents;

CellVerifiers::CustomConstraintCellGroup::CustomConstraintCellGroup(
        const std::vector<Cell::SharedPtr> &cells,
        std::function<bool(const std::vector<Cell::SharedPtr>&, int)>  constraint): CellVerifiers::CellGroup(cells),
        constraint(std::move(constraint)){}

bool CellVerifiers::CustomConstraintCellGroup::isNumberAllowed(int number) const{
    return this->constraint(this->cells, number);
}


