//
// Created by wojciech on 25.11.2021.
//

#include <algorithm>
#include "CellVerifiers/CellUniqueGroup.h"
#include "GameComponents/Cell.h"

using namespace std;
using GameComponents::Cell;

CellVerifiers::CellUniqueGroup::CellUniqueGroup(const std::vector<Cell::SharedPtr> &cells): CellGroup(cells) {
    for (int num = 1; num < 9; num++){
        this->usedNumberMask[num - 1] = true;
    }
    for (const auto &cell: cells) {
        if (!cell->isEmpty()){
            this->usedNumberMask[cell->getNumber() - 1] = false;
        }
    }
}

bool CellVerifiers::CellUniqueGroup::isNumberAllowed(int number) const{
    return this->usedNumberMask[number - 1];
}

void CellVerifiers::CellUniqueGroup::notifyAdd(int number) {
    this->usedNumberMask[number - 1] = false;
}

void CellVerifiers::CellUniqueGroup::notifyRemove(int number) {
    this->usedNumberMask[number - 1] = true;
}
