//
// Created by wojciech on 25.11.2021.
//

#include <algorithm>
#include "CellUniqueGroup.h"
#include "typedefs.h"
#include "memory"
#include "Cell.h"
#include "iostream"

using namespace std;

CellVerifiers::CellUniqueGroup::CellUniqueGroup(const std::vector<CellPtr> &cells): CellGroup(cells) {
    cout << this->cells.size() << endl;
}

bool CellVerifiers::CellUniqueGroup::isNumberAllowed(int number) {
    return !any_of(cells.begin(), cells.end(), [number](const CellPtr& cell){
        return cell->getNumber() == number;
    });
}