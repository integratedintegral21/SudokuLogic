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
        BOOST_TEST(*(circularSubsequentNumbersSequence.begin()) == 1);
        BOOST_TEST(*(circularSubsequentNumbersSequence.end()) == 9);
        BOOST_TEST(*(circularSubsequentNumbersSequence.startingNumber()) == 5);
    }
    BOOST_AUTO_TEST_CASE(IteratorIncrementationTest){
        // General case
        Solvers::CircularSubsequentNumbersSequence::Iterator it = circularSubsequentNumbersSequence.begin();
        for (int i = 2; i <= 9; ++i) {
            ++it;
            BOOST_TEST(*it == i);
        }
        ++it;
        BOOST_TEST(*it == 1);
        // Edge case (1 element)
        it = Solvers::CircularSubsequentNumbersSequence::Iterator(1, 1, 1);
        BOOST_TEST(*it == 1);
        BOOST_TEST(*(++it) == 1);
        // exceptions tests
        BOOST_CHECK_THROW(Solvers::CircularSubsequentNumbersSequence::Iterator(1, 0, 1), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(IteratorDecrementationTest){
        Solvers::CircularSubsequentNumbersSequence::Iterator it = circularSubsequentNumbersSequence.end();
        for (int i = 8; i >= 1; i--){
            --it;
            BOOST_TEST(*it == i);
        }
        --it;
        BOOST_TEST(*it == 9);
    }

BOOST_AUTO_TEST_SUITE_END()

