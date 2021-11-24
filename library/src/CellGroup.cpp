//
// Created by wojciech on 23.11.2021.
//

#include "CellGroup.h"
#include "Cell.h"

using namespace std;


CellGroup::CellGroup(std::array<CellPtr, 9> cells, std::array<CellPos, 9> cellPositions) {
    std::copy(cells.begin(), cells.end(), this->cells);
    std::copy(cellPositions.begin(), cellPositions.end(), this->cellPositions);
}

void CellGroup::updateAllowedNumbers() {
    for (const CellPtr& cellPtr: this->cells){
        for (int number = 1; number <= 9; number++){
            for (int i = 0; i < cells.size() ; i++){
                int cellRow = get<0>(cellPositions[i]);
                int cellCol = get<1>(cellPositions[i]);
                NumPosition numPosition = make_tuple(cellRow, cellCol, number);
                if (this->isNumberAllowed(numPosition)){
                    this->cells[i]->setNumberAllowed(number);
                }
                else{
                    this->cells[i]->setNumberNotAllowed(number);
                }
            }
        }
    }
}
