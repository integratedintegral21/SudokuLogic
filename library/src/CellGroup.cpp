//
// Created by wojciech on 23.11.2021.
//

#include "CellGroup.h"


CellGroup::CellGroup(std::array<const CellPtr, 9> cells, std::array<const CellPos, 9> cellPositions) {
    std::copy(cells.begin(), cells.end(), this->cells);
    std::copy(cellPositions.begin(), cellPositions.end(), this->cellPositions);
}

void CellGroup::updateAllowedNumbers() {
    for (const CellPtr cellPtr: this->cells){
        for (int number = 1; number <= 9; number++){

        }
    }
}
