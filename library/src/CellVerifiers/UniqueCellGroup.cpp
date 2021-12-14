//
// Created by wojciech on 12/12/2021.
//

#include "CellVerifiers/UniqueCellGroup.h"

void CellVerifiers::UniqueCellGroup::notifySet(int number) {
    this->allowanceMask[number - 1] = false;
}

void CellVerifiers::UniqueCellGroup::notifyClear(int number) {
    this->allowanceMask[number - 1] = true;
}

bool CellVerifiers::UniqueCellGroup::isNumberAllowed(int number) const {
    return this->allowanceMask[number - 1];
}

CellVerifiers::UniqueCellGroup::UniqueCellGroup() {
    for (int num = 1; num <= 9; num++){
        // group is empty by default
        this->allowanceMask[num - 1] = true;
    }
}

CellVerifiers::UniqueCellGroup::UniqueCellGroup(const CellVerifiers::UniqueCellGroup &uniqueCellGroup) {
    for (int num = 1; num <= 9; num++){
        // copy allowanceMask
        this->allowanceMask[num - 1] = uniqueCellGroup.isNumberAllowed(num);
    }
}
