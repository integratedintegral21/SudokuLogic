//
// Created by wojciech on 26/12/2021.
//

#include "boost/test/unit_test.hpp"
#include "SudokuSolvers/CircularSubsequentNumbersSequence.h"

struct TestSuiteCircularSequenceFixture{
    Solvers::CircularSubsequentNumbersSequence circularSubsequentNumbersSequence = Solvers::CircularSubsequentNumbersSequence(
            1, 9, 5);
    TestSuiteCircularSequenceFixture(){
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCirularSequence, TestSuiteCircularSequenceFixture)
    BOOST_AUTO_TEST_CASE(IterationMethodsTest){
        BOOST_TEST(*(circularSubsequentNumbersSequence.beginIt()) == 5);
        BOOST_TEST(*(circularSubsequentNumbersSequence.lastIt()) == 4);
    }
    BOOST_AUTO_TEST_CASE(IteratorIncrementationTest){
        // General case
        Solvers::CircularSubsequentNumbersSequence::Iterator it = circularSubsequentNumbersSequence.beginIt();
        for (int i = 6; i <= 9; ++i) {
            ++it;
            BOOST_TEST(*it == i);
        }
        for (int i = 1; i <= 5; ++i) {
            ++it;
            BOOST_TEST(*it == i);
        }
        // Edge case (1 element)
        it = Solvers::CircularSubsequentNumbersSequence::Iterator(1, 1, 1);
        BOOST_TEST(*it == 1);
        BOOST_TEST(*(++it) == 1);
        // exceptions tests
        BOOST_CHECK_THROW(Solvers::CircularSubsequentNumbersSequence::Iterator(1, 0, 1), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(IteratorDecrementationTest){
        Solvers::CircularSubsequentNumbersSequence::Iterator it = circularSubsequentNumbersSequence.lastIt();
        for (int i = 3; i >= 1; i--){
            --it;
            BOOST_TEST(*it == i);
        }
        for (int i = 9; i >= 4; i--){
            --it;
            BOOST_TEST(*it == i);
        }
    }

BOOST_AUTO_TEST_SUITE_END()

