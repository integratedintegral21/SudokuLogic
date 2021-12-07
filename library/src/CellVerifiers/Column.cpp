//
// Created by wojciech on 25.11.2021.
//

#include "CellVerifiers/Column.h"

using namespace CellVerifiers;

CellVerifiers::Column::Column(const std::vector<Cell::SharedPtr> &cells): CellVerifiers::CellUniqueGroup(cells) {}
