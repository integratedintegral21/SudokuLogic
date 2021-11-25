//
// Created by wojciech on 25.11.2021.
//

#include "Row.h"
#include "CellUniqueGroup.h"

CellVerifiers::Row::Row(const std::vector<CellPtr> &cells) : CellUniqueGroup(cells) {}
