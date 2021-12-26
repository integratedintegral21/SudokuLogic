//
// Created by wojciech on 13/12/2021.
//

#include "boost/test/unit_test.hpp"
#include "utils.h"
#include "GameComponents/Cell.h"
#include "GameComponents/Sudoku.h"
#include "SudokuSolvers/SingleThreadBacktrackingSolver.h"
#include <stdexcept>

using GameComponents::Cell;
using GameComponents::Sudoku;
using Solvers::SudokuSolver;
using Solvers::SingleThreadBacktrackingSolver;

using namespace std;

struct TestSuiteSudokuFixture{
    vector<Cell::SharedPtr> emptyBoard;
    vector<Cell::SharedPtr> emptyBoardWithGroups;

    vector<NumPosition> simpleBoardPoses = {
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

    vector<Cell::SharedPtr> simpleBoard;
    vector<Cell::SharedPtr> simpleBoardWithGroups;

    SudokuSolver::SharedPtr sudokuSolver;
    Sudoku::SharedPtr simpleSudoku;

    TestSuiteSudokuFixture(){
        for (int i = 0; i < 81; ++i) {
            emptyBoard.push_back(make_shared<Cell>());
        }
        emptyBoardWithGroups = Utils::getSimpleSudokuCells(emptyBoard);

        simpleBoard = Utils::getCellsFromNumPoses(simpleBoardPoses);
        simpleBoardWithGroups = Utils::getSimpleSudokuCells(simpleBoard);

        sudokuSolver = make_shared<SingleThreadBacktrackingSolver>();
        simpleSudoku = make_shared<Sudoku>(simpleBoardWithGroups, sudokuSolver);
    }
};

BOOST_FIXTURE_TEST_SUITE(SudokuTest, TestSuiteSudokuFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_REQUIRE(simpleSudoku != nullptr);

        BOOST_CHECK_THROW(make_shared<Sudoku>(vector<Cell::SharedPtr>(), sudokuSolver), invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(SimpleSudokuTest){
        // all number should be allowed in every cell of an empty board
        for (const auto &cell: emptyBoardWithGroups) {
            for (int num = 1; num <= 9; num++){
                BOOST_TEST(cell->isNumberAllowed(num));
            }
        }
        // are numbers in cells not allowed in their groups and are number not present in any of the groups allowed
        for (int i = 0; i < 81; ++i) {
            int rowIndex = i / 9;
            int columnIndex = i % 9;
            int boxInitialRow = (rowIndex / 3) * 3;
            int boxInitialCol = (columnIndex / 3) * 3;
            int number = simpleBoardWithGroups[i]->getNumber();

            vector<bool> rowNumbersPresence(9);
            vector<bool> columnNumbersPresence(9);
            vector<bool> boxNumbersPresence(9);
            for (int j = 0; j < 9; ++j) {
                rowNumbersPresence[j] = false;
                columnNumbersPresence[j] = false;
                boxNumbersPresence[j] = false;
            }
            // check current row
            for (int j = 0; j < 9; ++j) {
                int cellIndex = 9 * rowIndex + j;
                if(!simpleBoardWithGroups[cellIndex]->isEmpty()){
                    int num = simpleBoardWithGroups[cellIndex]->getNumber();
                    rowNumbersPresence[num - 1] = true;
                }
            }
            // check current column
            for (int j = 0; j < 9; ++j) {
                int cellIndex = 9 * j + columnIndex;
                if(!simpleBoardWithGroups[cellIndex]->isEmpty()){
                    int num = simpleBoardWithGroups[cellIndex]->getNumber();
                    columnNumbersPresence[num - 1] = true;
                }
            }
            // check current box
            for (int rowOffset = 0; rowOffset <= 2; ++rowOffset) {
                for (int columnOffset = 0; columnOffset <= 2; ++columnOffset) {
                    int cellIndex = 9 * (boxInitialRow + rowOffset) + boxInitialCol + columnOffset;
                    if(!simpleBoardWithGroups[cellIndex]->isEmpty()){
                        int num = simpleBoardWithGroups[cellIndex]->getNumber();
                        boxNumbersPresence[num - 1] = true;
                    }
                }
            }
            for (int num = 1; num <= 9; num++){
                if (rowNumbersPresence[num - 1] || columnNumbersPresence[num - 1] || boxNumbersPresence[num - 1]){
                    BOOST_TEST(!simpleBoardWithGroups[i]->isNumberAllowed(num));
                }
                else{
                    BOOST_TEST(simpleBoardWithGroups[i]->isNumberAllowed(num));
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE(SimpleSudokuAllowanceTest){
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                Cell::SharedPtr cell = this->simpleBoardWithGroups[9 * row + col];
                for (int num = 1; num <= 9; ++num){
                    BOOST_TEST(cell->isNumberAllowed(num) == simpleSudoku->isNumberAllowed(row, col, num));
                }
            }
        }
        BOOST_TEST(!simpleSudoku->isNumberAllowed(-1, 5, 5));
        BOOST_TEST(!simpleSudoku->isNumberAllowed(9, 5, 5));
        BOOST_TEST(!simpleSudoku->isNumberAllowed(5, 0, 5));
        BOOST_TEST(!simpleSudoku->isNumberAllowed(5, 9, 5));
        BOOST_TEST(!simpleSudoku->isNumberAllowed(5, 5, 0));
        BOOST_TEST(!simpleSudoku->isNumberAllowed(5, 5, 10));

        BOOST_TEST(simpleSudoku->isNumberAllowed(0, 1, 3));
        simpleSudoku->setNumber(0, 0, 3);
        BOOST_TEST(!simpleSudoku->isNumberAllowed(0, 1, 3));
    }

BOOST_AUTO_TEST_SUITE_END()
