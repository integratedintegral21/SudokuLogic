//
// Created by wojciech on 01/08/2021.
//

#include <Sudoku.h>
#include "boost/test/unit_test.hpp"
#include "utils.h"
#include <map>

using namespace std;

struct TestSuiteSudokuFixture{

    vector<NumPosition> board0 = {
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
    vector<NumPosition> allowedNumPoses = {
            make_tuple(1, 1, 4),
            make_tuple(1, 1, 3),
            make_tuple(7, 7, 8),
    };
    vector<NumPosition> invalidNumPoses = {
            make_tuple(1, 1, -5),
            make_tuple(-1, 1, 15),
            make_tuple(4, 12, 10),
            make_tuple(7, 7, 0),
    };
    vector<CellPos> invalidCellPoses = {
            make_tuple(1, -5),
            make_tuple(1, 15),
            make_tuple(-5, 10),
            make_tuple(7, 0),
    };
    vector<vector<CellPos>> simpleConstraints = getSimpleConstraints();
    SudokuPtr sudoku0;
    TestSuiteSudokuFixture(){
        sudoku0 = make_shared<Sudoku>(board0, simpleConstraints);
    }
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteSudoku, TestSuiteSudokuFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        for (NumPosition& numPosition: board0){
            CellPos cellPos = make_tuple(get<0>(numPosition), get<1>(numPosition));
            int expectedNumber = get<2>(numPosition);
            int actualNumber = sudoku0->getCellValue(cellPos);
            BOOST_REQUIRE(expectedNumber == actualNumber);
        }
    }

    BOOST_AUTO_TEST_CASE(CellValueTest){
        for(CellPos cellPos: invalidCellPoses){
            BOOST_CHECK_EXCEPTION(sudoku0->getCellValue(cellPos), invalid_argument, [](const logic_error& e){
                string expectedMsg = "CellPos invalid";
                return e.what() == expectedMsg;
            });
        }
    }

    BOOST_AUTO_TEST_CASE(NumberAllowanceTest){
        for (NumPosition numPosition: allowedNumPoses){
            BOOST_TEST(sudoku0->isNumberAllowed(numPosition));
        }
        for (NumPosition numPosition: invalidNumPoses){
            BOOST_CHECK_EXCEPTION(sudoku0->isNumberAllowed(numPosition), invalid_argument, [](const logic_error& e){
                string expectedMsg = "NumPosition invalid";
                return e.what() == expectedMsg;
            });
        }
        for(NumPosition numPosition: board0){
            int row = get<0>(numPosition);
            int col = get<1>(numPosition);
            int num = get<2>(numPosition);
            for (int rowIter = 1 ; rowIter <= 9; rowIter++){
                if(rowIter == row)
                    continue;
                NumPosition sameColumnPosition = make_tuple(rowIter, col, num);
                BOOST_TEST(!sudoku0->isNumberAllowed(sameColumnPosition));
            }
            for (int colIter = 1 ; colIter <= 9 ; colIter++){
                if (colIter == col)
                    continue;
                NumPosition sameRowPosition = make_tuple(row, colIter, num);
                BOOST_TEST(!sudoku0->isNumberAllowed(sameRowPosition));
            }
            vector<vector<CellPos>> cellConstraints;
            CellPos cellPos = make_tuple(row, col);
            for(vector<CellPos> con: simpleConstraints){
                for(CellPos pos: con){
                    if(pos == cellPos)
                        cellConstraints.push_back(con);
                }
            }
            for(vector<CellPos> con: cellConstraints){
                for(CellPos pos: con){
                    if (pos == cellPos)
                        continue;
                    int row = get<0>(pos);
                    int col = get<1>(pos);
                    BOOST_TEST(!sudoku0->isNumberAllowed(make_tuple(row, col, num)));
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE(FillingTest){
        for (NumPosition numPosition: invalidNumPoses){
            BOOST_CHECK_EXCEPTION(sudoku0->setNumber(numPosition), invalid_argument, [](const logic_error& e){
                string expectedMsg = "NumPosition invalid";
                return e.what() == expectedMsg;
            });
        }
        for (int row = 1 ; row <= 9 ; row++){
            for (int col = 1 ; col <= 9 ; col++){
                CellPos cellPos = make_tuple(row, col);
                if(sudoku0->getCellValue(cellPos) == -1)
                    continue;
                vector<int> allowedNumbers = sudoku0->getAllowedNumbers(9 * (row - 1) + col);
                for (int num: allowedNumbers){
                    this->sudoku0->setNumber(make_tuple(row, col, num));
                    BOOST_TEST(this->sudoku0->getCellValue(cellPos) == num);
                    this->sudoku0->unsetCell(cellPos);

                }
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()
