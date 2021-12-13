//
// Created by wojciech on 25.11.2021.
//


#include "boost/test/unit_test.hpp"
#include "CellVerifiers/UniqueCellGroup.h"
#include "CellVerifiers/IntegerSumCellGroup.h"
#include "GameComponents/Cell.h"

using namespace std;
using CellVerifiers::CellGroupObserver;
using CellVerifiers::UniqueCellGroup;
using CellVerifiers::IntegerSumCellGroup;
using GameComponents::Cell;

struct TestSuiteCellGroupFixture{
    vector<Cell::SharedPtr> cells;
    vector<CellGroupObserver::SharedPtr> groups;
    TestSuiteCellGroupFixture(){
        groups.push_back(make_shared<UniqueCellGroup>());
        // 1 + 2 + 3 + ... + 9 = 45
        groups.push_back(make_shared<IntegerSumCellGroup>(45, 9));
        for (int i = 0 ; i < 9 ; i++){
            cells.push_back(make_shared<Cell>());
            for (const auto &group: groups) {
                cells[i]->addGroupObserver(group);
            }
        }
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCellGroup, TestSuiteCellGroupFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        BOOST_REQUIRE(groups[0] != nullptr);
        BOOST_REQUIRE(groups[1] != nullptr);
    }

    BOOST_AUTO_TEST_CASE(UniqueCellGroupTest){
        auto uniqueGroup = groups[0];
        // are all allowed by default
        for (int num = 1; num <= 9; num++){
            BOOST_TEST(uniqueGroup->isNumberAllowed(num));
        }
        // is number is not allowed if set
        for (int num = 1; num <= 9; num++){
            cells[num - 1]->setNumber(num);
            BOOST_TEST(!uniqueGroup->isNumberAllowed(num));
        }
        // is allowed if unset
        for (int num = 1; num <= 9; num++){
            cells[num - 1]->clearCell();
            BOOST_TEST(uniqueGroup->isNumberAllowed(num));
        }
    }
BOOST_AUTO_TEST_SUITE_END()