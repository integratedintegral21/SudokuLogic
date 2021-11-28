//
// Created by wojciech on 25.11.2021.
//

#include <numeric>
#include "boost/test/unit_test.hpp"
#include "typedefs.h"
#include "CellGroup.h"
#include "memory"
#include "Row.h"
#include "Column.h"
#include "SquareBox.h"
#include "CustomConstraintCellGroup.h"
#include "Cell.h"
#include "functional"
#include "utils.h"

using namespace std;
using namespace CellVerifiers;

struct TestSuiteCellGroupFixture{
    shared_ptr<CellGroup> row;
    shared_ptr<CellGroup> col;
    shared_ptr<CellGroup> box;
    // all number must sum up to a certain number
    shared_ptr<CellGroup> sumGroup;
    vector<CellPtr> cells;
    // 1 + 2 + ... + 9 = 36
    const int expectedSum = 40;
    const function<bool(const vector<CellPtr>&, int)> sumConstraint = Utils::getSumConstraints(expectedSum);
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

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        BOOST_REQUIRE(this->row != nullptr);
        BOOST_REQUIRE(this->col != nullptr);
        BOOST_REQUIRE(this->box != nullptr);
        BOOST_REQUIRE(this->sumGroup != nullptr);
    }

    BOOST_AUTO_TEST_CASE(SumConstraintTest) {

    }

    BOOST_AUTO_TEST_CASE(AllowanceTest) {
        for (int number = 1; number <= 9 ; number++){
            int cellIndex = number - 1;
            // is the number allowed by default
            BOOST_TEST(row->isNumberAllowed(number));
            BOOST_TEST(col->isNumberAllowed(number));
            BOOST_TEST(box->isNumberAllowed(number));
            cells[cellIndex]->setNumber(number);
            // is the number no longer allowed
            BOOST_TEST(!row->isNumberAllowed(number));
            BOOST_TEST(!col->isNumberAllowed(number));
            BOOST_TEST(!box->isNumberAllowed(number));
            for (int allowedNumber = number + 1; allowedNumber <= 9 ; allowedNumber++){
                // are other number not allowed
                BOOST_TEST(row->isNumberAllowed(allowedNumber));
                BOOST_TEST(col->isNumberAllowed(allowedNumber));
                BOOST_TEST(box->isNumberAllowed(allowedNumber));
            }
        }
        // remove a number from each cell and check if it becomes allowed
        for (int number = 1; number <= 9 ; number++){
            int cellIndex = number - 1;
            cells[cellIndex]->unset();
            BOOST_TEST(row->isNumberAllowed(number));
            BOOST_TEST(col->isNumberAllowed(number));
            BOOST_TEST(box->isNumberAllowed(number));
        }
    }


BOOST_AUTO_TEST_SUITE_END()