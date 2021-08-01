//
// Created by wojciech on 01/08/2021.
//

#include "boost/test/unit_test.hpp"
#include "Cell.h"
#include "typedefs.h"
#include <memory>
#include <utils.h>
#include <Sudoku.h>

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
    vector<vector<CellPos>> simpleConstraints = getSimpleConstraints();
    TestSuiteSudokuFixture(){

    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteSudoku, TestSuiteSudokuFixture)

BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()