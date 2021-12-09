//
// Created by wojciech on 27.11.2021.
//

#include "CellVerifiers/CustomConstraintCellGroup.h"
#include <utility>

using namespace std;
using namespace GameComponents;

CellVerifiers::CustomConstraintCellGroup::CustomConstraintCellGroup(
        const std::vector<Cell::SharedPtr> &cells,
        std::function<bool(const std::vector<Cell::SharedPtr>&, int)>  constraint): CellVerifiers::CellGroup(cells),
        constraint(std::move(constraint)){
    for (const auto &cell: cells) {
        cell->addGroup(make_shared<CustomConstraintCellGroup>(*this));
    }
}

bool CellVerifiers::CustomConstraintCellGroup::isNumberAllowed(int number) const{
    return this->constraint(this->cells, number);
}

void CellVerifiers::CustomConstraintCellGroup::notifyAdd(int number) {

}

void CellVerifiers::CustomConstraintCellGroup::notifyRemove(int number) {

}


