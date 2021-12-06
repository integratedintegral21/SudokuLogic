//
// Created by wojciech on 25.11.2021.
//

#include "CellVerifiers/Row.h"
#include "CellVerifiers/CellUniqueGroup.h"

CellVerifiers::Row::Row(const std::vector<CellPtr> &cells) : CellUniqueGroup(cells) {}
