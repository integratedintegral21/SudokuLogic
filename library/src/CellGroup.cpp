//
// Created by wojciech on 23.11.2021.
//

#include "CellGroup.h"
#include "Cell.h"

using namespace std;


CellGroup::CellGroup(std::array<CellPtr, 9> cells) {
    std::copy(cells.begin(), cells.end(), this->cells);
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

void CellGroup::setNumberNotAllowed(int number) {
    for (const CellPtr& cellPtr: this->cells){
        cellPtr->setNumberNotAllowed(number);
    }
}
