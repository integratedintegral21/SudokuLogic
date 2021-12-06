//
// Created by wojciech on 23.11.2021.
//

#include "CellVerifiers/CellGroup.h"
#include "GameComponents/Cell.h"
#include "iostream"

using namespace std;

CellVerifiers::CellGroup::CellGroup(const vector<CellPtr> &cells) {
    for (const CellPtr& cell: cells){
        this->cells.push_back(cell);
    }
}

std::vector<CellPtr> CellVerifiers::CellGroup::getCells() const {
    return std::vector<CellPtr>(this->cells);
}

bool CellVerifiers::CellGroup::isNumberAllowed(int number) const {
    return false;
}

