//
// Created by wojciech on 28/07/2021.
//

#include "boost/test/unit_test.hpp"
#include "GameComponents/Cell.h"
#include "CellVerifiers/UniqueCellGroup.h"
#include <stdexcept>

using namespace std;
using GameComponents::Cell;
using CellVerifiers::UniqueCellGroup;
using CellVerifiers::CellGroupObserver;

struct TestSuiteCellFixture{
    int number = 1;
    Cell::SharedPtr cell;
    Cell::SharedPtr emptyCell;
    CellGroupObserver::SharedPtr groupObserver = make_shared<UniqueCellGroup>();
    TestSuiteCellFixture(){
        cell = make_shared<Cell>(number);
        emptyCell = make_shared<Cell>();
        cell->addGroupObserver(groupObserver);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCell, TestSuiteCellFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_REQUIRE(cell != nullptr);
        BOOST_REQUIRE(emptyCell != nullptr);

        BOOST_TEST(!groupObserver->isNumberAllowed(number));

        BOOST_TEST(!cell->isEmpty());
        BOOST_TEST(emptyCell->isEmpty());

        BOOST_TEST(cell->getNumber() == number);
        BOOST_TEST(emptyCell->getNumber() == 0);
    }

    BOOST_AUTO_TEST_CASE(SettersTest){
        cell->setNumber(5);
        BOOST_TEST(cell->getNumber() == 5);

        cell->clearCell();
        BOOST_TEST(cell->getNumber() == 0);
        BOOST_TEST(cell->isEmpty());
        // double cleared cell
        cell->clearCell();
        BOOST_TEST(cell->isEmpty());

        BOOST_CHECK_THROW(cell->setNumber(-1), invalid_argument);
        BOOST_CHECK_THROW(cell->setNumber(0), invalid_argument);
        BOOST_CHECK_THROW(cell->setNumber(10), invalid_argument);
        BOOST_CHECK_THROW(cell->setNumber(11), invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(GroupObserversTest){
        vector<CellGroupObserver::SharedPtr> groups = cell->getGroups();
        BOOST_TEST(cell->getGroups().size() == 1);

        // separation test
        groups[0] = make_shared<UniqueCellGroup>();
        BOOST_TEST(cell->getGroups() != groups);
    }

    BOOST_AUTO_TEST_CASE(CloneTest){
        groupObserver->notifySet(number);
        Cell::SharedPtr cellClone = cell->clone();
        BOOST_TEST(cellClone->getNumber() == number);
        BOOST_TEST(!cellClone->isNumberAllowed(number));
    }

BOOST_AUTO_TEST_SUITE_END()
