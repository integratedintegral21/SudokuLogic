//
// Created by wojciech on 01/08/2021.
//

#include <Sudoku.h>
#include "boost/test/unit_test.hpp"
#include "utils.h"
#include <map>

using namespace std;

struct TestSuiteSudokuFixture{
    vector<vector<NumPosition>> simpleBoards = {
            {
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
            },
    };
    vector<vector<NumPosition>> hardBoards = {
            {
                    make_tuple(1,7,2),
                    make_tuple(2,2,8),
                    make_tuple(2,6,7),
                    make_tuple(2,8,9),
                    make_tuple(3,1,6),
                    make_tuple(3,3,2),
                    make_tuple(3,7,5),
                    make_tuple(4,2,7),
                    make_tuple(4,5,6),
                    make_tuple(5,4,9),
                    make_tuple(5,6,1),
                    make_tuple(6,5,2),
                    make_tuple(6,8,4),
                    make_tuple(7,3,5),
                    make_tuple(7,7,6),
                    make_tuple(7,9,3),
                    make_tuple(8,2,9),
                    make_tuple(8,4,4),
                    make_tuple(8,8,7),
                    make_tuple(9,3,6),
            },
    };
    vector<NumPosition> emptyBoard;
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
    vector<SudokuPtr> simpleSudokus;
    SudokuPtr emptySudoku;
    TestSuiteSudokuFixture(){
        for(vector<NumPosition>& board : simpleBoards){
            simpleSudokus.push_back(make_shared<Sudoku>(board, simpleConstraints));
        }
        emptySudoku = make_shared<Sudoku>(emptyBoard, simpleConstraints);
    }
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteSudoku, TestSuiteSudokuFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        for (int i = 0 ; i < simpleSudokus.size() ; i++) {
            auto board = simpleBoards[i];
            auto sudoku = simpleSudokus[i];
            for (NumPosition &numPosition: board) {
                CellPos cellPos = make_tuple(get<0>(numPosition), get<1>(numPosition));
                int expectedNumber = get<2>(numPosition);
                int actualNumber = sudoku->getCellValue(cellPos);
                BOOST_REQUIRE(expectedNumber == actualNumber);
            }
        }
        for (NumPosition& numPosition: emptyBoard){
            CellPos cellPos = make_tuple(get<0>(numPosition), get<1>(numPosition));
            int expectedNumber = get<2>(numPosition);
            int actualNumber = emptySudoku->getCellValue(cellPos);
            BOOST_REQUIRE(expectedNumber == actualNumber);
        }
    }

    BOOST_AUTO_TEST_CASE(CellValueTest){
        auto sudoku0 = simpleSudokus[0];
        for (CellPos cellPos: invalidCellPoses) {
            BOOST_CHECK_EXCEPTION(sudoku0->getCellValue(cellPos), invalid_argument, [](const logic_error &e) {
                string expectedMsg = "CellPos invalid";
                return e.what() == expectedMsg;
            });
        }

    }

    BOOST_AUTO_TEST_CASE(NumberAllowanceTest){
        auto sudoku0 = simpleSudokus[0];
        for (NumPosition& numPosition: allowedNumPoses){
            BOOST_TEST(sudoku0->isNumberAllowed(numPosition));
        }
        for (NumPosition& numPosition: invalidNumPoses){
            BOOST_CHECK_EXCEPTION(sudoku0->isNumberAllowed(numPosition), invalid_argument, [](const logic_error& e){
                string expectedMsg = "NumPosition invalid";
                return e.what() == expectedMsg;
            });
        }
        for (NumPosition& numPosition: emptyBoard){
            int row = get<0>(numPosition);
            int col = get<1>(numPosition);
            for (int num = 1 ; num <= 9 ; num++){
                BOOST_TEST(emptySudoku->isNumberAllowed(make_tuple(row, col, num)));
            }
        }
        for (int i = 0 ; i < simpleSudokus.size() ; i++) {
            auto board = simpleBoards[i];
            auto sudoku = simpleSudokus[i];
            for (NumPosition &numPosition: board) {
                int row = get<0>(numPosition);
                int col = get<1>(numPosition);
                int num = get<2>(numPosition);
                for (int rowIter = 1; rowIter <= 9; rowIter++) {
                    if (rowIter == row)
                        continue;
                    NumPosition sameColumnPosition = make_tuple(rowIter, col, num);
                    BOOST_TEST(!sudoku->isNumberAllowed(sameColumnPosition));
                }
                for (int colIter = 1; colIter <= 9; colIter++) {
                    if (colIter == col)
                        continue;
                    NumPosition sameRowPosition = make_tuple(row, colIter, num);
                    BOOST_TEST(!sudoku->isNumberAllowed(sameRowPosition));
                }
                vector<vector<CellPos>> cellConstraints;
                CellPos cellPos = make_tuple(row, col);
                for (vector<CellPos> con: simpleConstraints) {
                    for (CellPos pos: con) {
                        if (pos == cellPos)
                            cellConstraints.push_back(con);
                    }
                }
                for (vector<CellPos> &con: cellConstraints) {
                    for (CellPos pos: con) {
                        if (pos == cellPos)
                            continue;
                        int row = get<0>(pos);
                        int col = get<1>(pos);
                        BOOST_TEST(!sudoku->isNumberAllowed(make_tuple(row, col, num)));
                    }
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE(FillingTest){
        auto sudoku0 = simpleSudokus[0];
        for (NumPosition numPosition: invalidNumPoses){
            BOOST_CHECK_EXCEPTION(sudoku0->setNumber(numPosition), invalid_argument, [](const logic_error& e){
                string expectedMsg = "NumPosition invalid";
                return e.what() == expectedMsg;
            });
        }
        for (int i = 0 ; i < simpleSudokus.size() ; i++) {
            auto board = simpleBoards[i];
            auto sudoku = simpleSudokus[i];
            for (int row = 1; row <= 9; row++) {
                for (int col = 1; col <= 9; col++) {
                    CellPos cellPos = make_tuple(row, col);
                    if (sudoku->getCellValue(cellPos) == -1)
                        continue;
                    vector<int> allowedNumbers = sudoku->getAllowedNumbers(9 * (row - 1) + col);
                    for (int num: allowedNumbers) {
                        sudoku->setNumber(make_tuple(row, col, num));
                        BOOST_TEST(sudoku->getCellValue(cellPos) == num);
                        sudoku->unsetCell(cellPos);

                    }
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE(SolveTest){
        for (int i = 0 ; i < simpleSudokus.size() ; i++) {
            auto board = simpleBoards[i];
            auto sudoku = simpleSudokus[i];
            sudoku->solve();
            BOOST_TEST(sudoku->isSolved());
            for (int row = 1; row <= 9; row++) {
                for (int col = 1; col <= 9; col++) {
                    int num = sudoku->getCellValue(make_tuple(row, col));
                    // non-repetitive in current column
                    for (int checkRow = 1; checkRow <= 9; checkRow++) {
                        if (checkRow == row)
                            continue;
                        BOOST_TEST(sudoku->getCellValue(make_tuple(checkRow, col)) != num);
                    }
                    // non-repetitive in current row
                    for (int checkCol = 1; checkCol <= 9; checkCol++) {
                        if (checkCol == col)
                            continue;
                        BOOST_TEST(sudoku->getCellValue(make_tuple(row, checkCol)) != num);
                    }
                }
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()
