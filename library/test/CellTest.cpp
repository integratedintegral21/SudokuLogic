//
// Created by wojciech on 28/07/2021.
//
#include "boost/test/unit_test.hpp"
#include "Cell.h"
#include "typedefs.h"
#include <memory>

using namespace std;

struct TestSuiteCellFixture{
    int number0 = 7;
    int validNumbers[3] = {
            5,1,9
    };
    int invalidNumbers[3] = {
            11, 0, 10
    };

    CellPtr cell0;
    CellPtr cell1;

    TestSuiteCellFixture(){
        cell0 = make_shared<Cell>();
        cell1 = make_shared<Cell>(number0);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCell, TestSuiteCellFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_TEST(cell0->getNumber() == -1);
        BOOST_TEST(cell1->getNumber() == number0);

        for(int num = 1 ; num <= 9 ; num++){
            BOOST_TEST(cell0->isNumberPossible(num) == false);
            BOOST_TEST(cell1->isNumberPossible(num) == false);
        }
    }
    BOOST_AUTO_TEST_CASE(NumberSetterTest) {
        for (int num: validNumbers){
            cell0->setNumber(num);
            BOOST_TEST(cell0->getNumber() == num);
        }
        int currentNumber = cell0->getNumber();
        for (int num: invalidNumbers){
            cell0->setNumber(num);
            BOOST_TEST(cell0->getNumber() == currentNumber);
        }
    }
    BOOST_AUTO_TEST_CASE(IsEmptyTest) {
        BOOST_TEST(cell0->isEmpty() == true);
        BOOST_TEST(cell1->isEmpty() == false);

        cell0->setNumber(validNumbers[0]);
        cell1->setNumber(validNumbers[0]);

        BOOST_TEST(cell0->isEmpty() == false);
        BOOST_TEST(cell1->isEmpty() == false);
    }

    BOOST_AUTO_TEST_CASE(PossibleNumbersTest){

    }

BOOST_AUTO_TEST_SUITE_END()
