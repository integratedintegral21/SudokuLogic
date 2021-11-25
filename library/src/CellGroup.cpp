//
// Created by wojciech on 23.11.2021.
//

#include "CellGroup.h"
#include "Cell.h"
#include "iostream"

using namespace std;

CellVerifiers::CellGroup::CellGroup(const vector<CellPtr> &cells) {
    for (const CellPtr& cell: cells){
        this->cells.push_back(cell);
    }
}

