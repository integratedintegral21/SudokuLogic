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
    // 1 + 2 + ... + 9 = 45
    const int expectedSum = 45;
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

    BOOST_AUTO_TEST_CASE(GetterTest) {
        vector<CellPtr> getRowResult = row->getCells();
        vector<CellPtr> getColResult = col->getCells();
        vector<CellPtr> getBoxResult = box->getCells();
        vector<CellPtr> getSumResult = sumGroup->getCells();
        for (int i = 0 ; i < cells.size(); i++){
            BOOST_TEST(cells[i] == getRowResult[i]);
            BOOST_TEST(cells[i] == getColResult[i]);
            BOOST_TEST(cells[i] == getBoxResult[i]);
            BOOST_TEST(cells[i] == getSumResult[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(SumConstraintTest) {
        // Single cell case
        vector<CellPtr> cells1= {
                make_shared<Cell>()
        };
        const function<bool(const vector<CellPtr>&, int)> sumConstraint1 = Utils::getSumConstraints(4);
        BOOST_TEST(sumConstraint1(cells1, 4));
        BOOST_TEST(!sumConstraint1(cells1, 3));
        BOOST_TEST(!sumConstraint1(cells1, 5));
        // More than one cell case
        cells1 = {
                make_shared<Cell>(),
                make_shared<Cell>(),
        };
        // Does leave space for more numbers (a non-final candidate case)
        BOOST_TEST(sumConstraint1(cells1, 3));
        BOOST_TEST(!sumConstraint1(cells1, 4));
        BOOST_TEST(!sumConstraint1(cells1, 5));

        cells1[0]->setNumber(2);
        BOOST_TEST(sumConstraint1(cells1, 2));
        BOOST_TEST(!sumConstraint1(cells1, 1));
        BOOST_TEST(!sumConstraint1(cells1, 5));
    }

    BOOST_AUTO_TEST_CASE(UniqueAllowanceTest) {
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
                // are other number still allowed
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

    BOOST_AUTO_TEST_CASE(SumAllowanceTest){
        for (int num = 9; num >= 3 ; num--){
            sumGroup->isNumberAllowed(num);
            cells[num - 1]->setNumber(num);
        }
        // two slots left, check if a candidate leaves space for next numbers
        BOOST_TEST(sumGroup->isNumberAllowed(1));
        BOOST_TEST(sumGroup->isNumberAllowed(2));
        BOOST_TEST(!sumGroup->isNumberAllowed(3));
        BOOST_TEST(!sumGroup->isNumberAllowed(4));

        cells[1]->setNumber(2);
        // one slot left, only 1 is allowed
        BOOST_TEST(sumGroup->isNumberAllowed(1));
        BOOST_TEST(!sumGroup->isNumberAllowed(2));
    }
    BOOST_AUTO_TEST_CASE(SimpleSudokuGroupsTest){
        vector<NumPosition> simpleBoard = {
                make_tuple(1, 4, 2),
                make_tuple(1, 5, 6),
                make_tuple(1, 7, 7),
                make_tuple(1, 9, 1),
                make_tuple(2, 1, 6),
                make_tuple(2, 2, 8),
                make_tuple(2, 5, 7),
                make_tuple(2, 8, 9),
                make_tuple(3, 1, 1),
                make_tuple(3 ,2, 9),
                make_tuple(3 ,6, 4),
                make_tuple(3 ,7 ,5),
                make_tuple(4, 1, 8),
                make_tuple(4, 2, 2),
                make_tuple(4, 4, 1),
                make_tuple(4, 8, 4),
                make_tuple(5, 3, 4),
                make_tuple(5, 4, 6),
                make_tuple(5, 6, 2),
                make_tuple(5, 7, 9),
                make_tuple(6, 2, 5),
                make_tuple(6, 6, 3),
                make_tuple(6, 8, 2),
                make_tuple(6, 9, 8),
                make_tuple(7, 3, 9),
                make_tuple(7, 4, 3),
                make_tuple(7, 8, 7),
                make_tuple(7, 9, 4),
                make_tuple(8, 2, 4),
                make_tuple(8, 5, 5),
                make_tuple(8, 8, 3),
                make_tuple(8, 9, 6),
                make_tuple(9, 1, 7),
                make_tuple(9, 3, 3),
                make_tuple(9, 5, 1),
                make_tuple(9, 6, 8),
        };
        vector<CellPtr> cells = Utils::getCellsFromNumPoses(simpleBoard);
        vector<CellGroup::SharedPtr> cellGroups = Utils::getSimpleGroups(cells);
        BOOST_TEST(cellGroups.size() == 27);
        vector<CellGroup::SharedPtr> rows(9);
        vector<CellGroup::SharedPtr> cols(9);
        vector<CellGroup::SharedPtr> boxes(9);
        copy(cellGroups.begin(), cellGroups.begin() + 9, rows.begin());
        copy(cellGroups.begin() + 9, cellGroups.begin() + 18, cols.begin());
        copy(cellGroups.begin() + 18, cellGroups.begin() + 27, boxes.begin());
        // check if not present numbers are allowed in groups and present numbers are not allowed
        for (int i = 0; i < 9; i++){
            int row = i, col = i, box = i;
            // already inside a group
            vector <int> notAllowedRow;
            vector <int> notAllowedCol;
            vector <int> notAllowedBox;
            for (int colIndex = 0; colIndex < 9; colIndex++){
                if (!cells[9 * row + colIndex]->isEmpty()){
                    notAllowedRow.push_back(cells[9 * row + colIndex]->getNumber());
                }
            }
            for (int rowIndex = 0; rowIndex < 9; rowIndex++){
                if (!cells[9 * rowIndex + col]->isEmpty()){
                    notAllowedCol.push_back(cells[9 * rowIndex + col]->getNumber());
                }
            }
            int boxInitialRow = i / 3 * 3;
            int boxInitialCol = i % 3 * 3;
            for (int rowOffset = 0; rowOffset <= 2; rowOffset++){
                for (int colOffset = 0; colOffset <= 2; colOffset++){
                    int cellIndex = 9 * (boxInitialRow + rowOffset) + (boxInitialCol + colOffset);
                    if (!cells[cellIndex]->isEmpty()){
                        notAllowedBox.push_back(cells[cellIndex]->getNumber());
                    }
                }
            }
            vector <bool> allowedRowMask(10);
            vector <bool> allowedColMask(10);
            vector <bool> allowedBoxMask(10);
            for (int j = 0; j < 10; j++){
                allowedRowMask[j] = true;
                allowedColMask[j] = true;
                allowedBoxMask[j] = true;
            }
            for (int num: notAllowedRow){
                allowedRowMask[num] = false;
            }
            for (int num: notAllowedCol){
                allowedColMask[num] = false;
            }
            for (int num: notAllowedBox){
                allowedBoxMask[num] = false;
            }
            for (int num = 1; num <= 9; num++){
                BOOST_TEST(rows[i]->isNumberAllowed(num) == allowedRowMask[num]);
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()