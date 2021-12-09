//
// Created by wojciech on 25.11.2021.
//

#include <numeric>
#include "boost/test/unit_test.hpp"
#include "typedefs.h"
#include "CellVerifiers/CellGroup.h"
#include "memory"
#include "CellVerifiers/Row.h"
#include "CellVerifiers/Column.h"
#include "CellVerifiers/SquareBox.h"
#include "CellVerifiers/CustomConstraintCellGroup.h"
#include "GameComponents/Cell.h"
#include "functional"
#include "utils.h"

using namespace std;
using namespace CellVerifiers;
using namespace GameComponents;

struct TestSuiteCellGroupFixture{
    shared_ptr<CellGroup> row;
    shared_ptr<CellGroup> col;
    shared_ptr<CellGroup> box;
    // all number must sum up to a certain number
    shared_ptr<CellGroup> sumGroup;
    vector<Cell::SharedPtr> cells;
    // 1 + 2 + ... + 9 = 45
    const int expectedSum = 45;
    const function<bool(const vector<Cell::SharedPtr>&, int)> sumConstraint = Utils::getSumConstraints(expectedSum);
    TestSuiteCellGroupFixture(){
        for (int i = 0 ; i < 9 ; i++)
            cells.push_back(make_shared<Cell>());
        row = make_shared<Row>(cells);
        col = make_shared<Column>(cells);
        box = make_shared<SquareBox>(cells);
        sumGroup = make_shared<CustomConstraintCellGroup>(cells, sumConstraint);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCellGroup, TestSuiteCellGroupFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_REQUIRE(row != nullptr);
        BOOST_REQUIRE(col != nullptr);
        BOOST_REQUIRE(box != nullptr);
        row->isNumberAllowed(4);
        int a = 0;
    }
BOOST_AUTO_TEST_SUITE_END()