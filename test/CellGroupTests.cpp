//
// Created by wojciech on 25.11.2021.
//

#include <numeric>
#include "boost/test/unit_test.hpp"
#include "typedefs.h"
#include "CellVerifiers/CellGroupObserver.h"
#include "memory"
#include "CellVerifiers/Row.h"
#include "CellVerifiers/Column.h"
#include "CellVerifiers/SquareBox.h"
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
    vector<Cell::SharedPtr> cells;
    TestSuiteCellGroupFixture(){
        for (int i = 0 ; i < 9 ; i++)
            cells.push_back(make_shared<Cell>());
        row = make_shared<Row>(cells);
        col = make_shared<Column>(cells);
        box = make_shared<SquareBox>(cells);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCellGroup, TestSuiteCellGroupFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_REQUIRE(row != nullptr);
        BOOST_REQUIRE(col != nullptr);
        BOOST_REQUIRE(box != nullptr);
    }

    BOOST_AUTO_TEST_CASE(UniquenessTest){
        for (int num = 1; num <= 9; num++){
            cells[num - 1]->setNumber(num);
            BOOST_TEST(!row->isNumberAllowed(num));
        }
    }
BOOST_AUTO_TEST_SUITE_END()