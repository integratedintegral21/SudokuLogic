//
// Created by wojciech on 23.11.2021.
//

#include "CellVerifiers/CellGroup.h"
#include "GameComponents/Cell.h"

using namespace std;
using CellVerifiers::CellGroup;
using GameComponents::Cell;

CellVerifiers::CellGroup::CellGroup(const vector<GameComponents::Cell::SharedPtr> &cells) {
    for (const Cell::SharedPtr& cell: cells){
        this->cells.push_back(cell);
        cell->addGroup(shared_ptr<CellGroup>(this));
    }
}

std::vector<Cell::SharedPtr> CellVerifiers::CellGroup::getCells() const {
    return std::vector<Cell::SharedPtr>(this->cells);
}

CellVerifiers::CellGroup::~CellGroup() {
    for (const Cell::SharedPtr& cell: this->cells) {
        cell->removeGroup(shared_ptr<CellGroup>(this));
    }
}
