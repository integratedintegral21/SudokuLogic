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

std::shared_ptr<CellVerifiers::CellGroupObserver> CellVerifiers::UniqueCellGroup::clone() const {
    std::shared_ptr<CellGroupObserver> newGroup = std::make_shared<UniqueCellGroup>();
    for (int i = 0; i < 9; ++i) {
        if (!allowanceMask[i]){
            newGroup->notifySet(i + 1);
        }
    }
    return newGroup;
}

