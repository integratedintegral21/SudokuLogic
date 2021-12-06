//
// Created by wojciech on 25.11.2021.
//

#include <algorithm>
#include "CellVerifiers/CellUniqueGroup.h"
#include "typedefs.h"
#include "memory"
#include "GameComponents/Cell.h"
#include "iostream"

using namespace std;

CellVerifiers::CellUniqueGroup::CellUniqueGroup(const std::vector<CellPtr> &cells): CellGroup(cells) {}

bool CellVerifiers::CellUniqueGroup::isNumberAllowed(int number) const{
    return !any_of(cells.begin(), cells.end(), [number](const CellPtr& cell){
        return cell->getNumber() == number;
    });
}