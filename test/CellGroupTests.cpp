//
// Created by wojciech on 25.11.2021.
//

#include "boost/test/unit_test.hpp"
#include "typedefs.h"
#include "CellGroup.h"
#include "memory"
#include "Row.h"
#include "Column.h"
#include "SquareBox.h"
#include "Cell.h"

using namespace std;
using namespace CellVerifiers;

struct TestSuiteCellGroupFixture{
    shared_ptr<CellGroup> row;
    shared_ptr<CellGroup> col;
    shared_ptr<CellGroup> box;
    vector<CellPtr> cells;
    TestSuiteCellGroupFixture(){
        for (int i = 0 ; i < 9 ; i++)
            cells.push_back(make_shared<Cell>());
        row = make_shared<Row>(cells);
        col = make_shared<Column>(cells);
        box = make_shared<SquareBox>(cells);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCellGroup, TestSuiteCellGroupFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        BOOST_REQUIRE(this->row != nullptr);
        BOOST_REQUIRE(this->col != nullptr);
        BOOST_REQUIRE(this->box != nullptr);
    }

    BOOST_AUTO_TEST_CASE(AllowanceTest) {
        for (int number = 1; number <= 9 ; number++){
            int cellIndex = number - 1;
            cells[cellIndex]->setNumber(number);
            BOOST_TEST(!row->isNumberAllowed(number));
        }
    }


BOOST_AUTO_TEST_SUITE_END()